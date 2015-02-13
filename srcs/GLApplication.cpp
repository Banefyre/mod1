#include <Landscape.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Waterscape.hpp>
#include "../includes/Cube.hpp"
#include "../includes/GLApplication.hpp" 					// Include our main header for the application

ModelManager land;										    // Our class to handle initializing and drawing our landscape
ModelManager water;
ModelManager rain;

//Coplien defs
GLApplication::GLApplication()
{
};

GLApplication::GLApplication(GLApplication const &src) {
    *this = src;
    return ;
}

GLApplication&		GLApplication::operator=(GLApplication const & rhs) {

    _windowManager = rhs.getWindowManager();
    _camera = rhs.getCamera();

return *this;
}

Camera* GLApplication::getCamera()const { return _camera; };

WindowManager* GLApplication::getWindowManager()const { return _windowManager; }

// This function initializes the window, the shaders and the triangle vertex data.
void GLApplication::initialize(std::string map)
{
    // Make sure the window manager is initialized prior to calling this and creates the OpenGL context
    if ( !_windowManager || _windowManager->initialize(screenWidth, screenHeight, "mod1", false) != 0 )
    {
        // Quit the application if the window couldn't be created with an OpenGL context
        exit(-1);
    }

    // Tell OpenGL that we want a 3D viewport the same size as the window
    glViewport(0, 0, screenWidth, screenHeight);

    // This tells OpenGL that we want depth testing so it renders the order correctly
    glEnable(GL_DEPTH_TEST);


    //Draw our landscape;
    landscape.initMap(map);


    // Initialize the model with the vertex array and give the vertex length of 120
    land.initialize(landscape.vertab, landscape.size , "Shaders/Shader.vertex", "Shaders/Shader.fragment");


    std::cout << landscape.size << std::endl;


    // Create the projection matrix from our camera and make the near field closer and the far field farther.
    // This makes it so our tower doesn't get cut off and also doesn't cull geometry right near the camera.
    //									 FOV		    Aspect Ratio			   Near / Far Planes
    _camera->setPerspective(glm::radians(60.0f), screenWidth / (float)screenHeight, 0.01f, 1000);

    // Below we call our init function for our camera to give it a position, a yaw and a pitch rotation.
    // 0 for a yaw and pitch will put the camera looking directly down the negative z-axis.  We don't
    // do any rotations yet so a different pitch or yaw won't do anything until our next tutorial.

    //					                Position	            Yaw	            Pitch
    _camera->positionCamera(-17.7735, 50.4207, -12.1607,		2.20118,		0.830997);

    // We now pass in the camera to have access to the projection and view matrices
    land.setCamera(_camera);

    // Set the position of the first triangle to be at the origin
    land.setPosition(vec3(0, 0, 0));

    Cube cube;
    water.initialize(cube.watervertab, 36, "Shaders/Shader.vertex", "Shaders/Shader.fragment");

    // We now pass in the camera to have access to the projection and view matrices
    water.setCamera(_camera);

    // Set the position of the first triangle to be at the origin
    water.setPosition(vec3(5, 5, 5));

    Cube raindrop;
    rain.initialize(raindrop.watervertab, 36, "Shaders/Shader.vertex", "Shaders/Shader.fragment");
    rain.setCamera(_camera);
    rain.setScale(vec3(0.2f));
}


void GLApplication::waterUpdate() {

    if (scenario == "rain")
    {
        c -= TimeManager::Instance().deltaTime;

        if (c < 0)
        {
            //init a new raindrop
            int x = rand()%49;
            int z = rand()%49;
            rainPos.push_back(new vec3(x, 150, z));

            c = 0.001f;
        }

        for(std::vector<vec3*>::iterator it=rainPos.begin(); it!=rainPos.end(); ++it)
        {
            vec3* el = *it;
            el->y -= 100.0f * TimeManager::Instance().deltaTime;
            //std::cout << el.y << std::endl;
            if(el->y <= (waterscape.waterHeights[el->x][el->z] + landscape.heights[el->x][el->z]))
            {
                waterscape.waterHeights[el->x][el->z] += 0.5;
                rainPos.erase(it);
                delete el;
            }else {
                rain.setPosition(*el);
                rain.render();
            }
        }
    }

    if (scenario == "rise")
    {
        for (int x = 0 ; x < landscape.getWidth(); x++) {
            for (int z = 0; z < landscape.getHeight(); z++) {
                    if (waterscape.waterHeights[x][z] > 0.0000)
                    {
                        waterscape.waterHeights[x][z] += 0.9 * TimeManager::Instance().deltaTime;
                    }
            }
        }
    }
    if (scenario == "empty")
    {
        for (int x = 0 ; x < landscape.getWidth(); x++) {
            for (int z = 0; z < landscape.getHeight(); z++) {
                if (waterscape.waterHeights[x][z] > 1.0f) {
                        waterscape.waterHeights[x][z] -= 1.0f * TimeManager::Instance().deltaTime;
                }
                else {
                    waterscape.waterHeights[x][z] = 0.0f;
                }
            }
        }
    }
    for (int x = 0 ; x < landscape.getWidth() -1; x++)
    {
        for (int z = 0 ; z < landscape.getHeight()-1; z++)
        {
            if (waterscape.waterHeights[x][z] > 0.000)
            {
                //check les cases autour + recupere la case la moins haute (terre+eau)

                float minHeight = landscape.heights[x][z] + waterscape.waterHeights[x][z];
                int minX = x;
                int minZ = z;

                for (int xx = x - 1; xx <= x + 1 ; xx++) {
                    for (int zz = z - 1 ; zz <= z + 1 ; zz++) {
                        if (xx >= 0 && xx < waterscape.getWidth()  && zz >= 0 && zz < waterscape.getHeight() ) {
                            if ((waterscape.waterHeights[xx][zz] +  landscape.heights[xx][zz]) < minHeight) {
                                minHeight = (waterscape.waterHeights[xx][zz] + landscape.heights[xx][zz]);
                                minX = xx;
                                minZ = zz;
                            }
                        }
                    }
                }

                if (minX != x || minZ != z) {
                    //equillibre min case avec l'eau de la current case
                    float average = (waterscape.waterHeights[x][z] + landscape.heights[x][z] + waterscape.waterHeights[minX][minZ] + landscape.heights[minX][minZ]) / 2;
                    float toFill = average - (waterscape.waterHeights[minX][minZ] + landscape.heights[minX][minZ]);

                    if (toFill > waterscape.waterHeights[x][z]) {
                        waterscape.waterHeights[minX][minZ] += waterscape.waterHeights[x][z];
                        waterscape.waterHeights[x][z] = 0.0;
                    }
                    else {
                        waterscape.waterHeights[x][z] -= toFill;
                        waterscape.waterHeights[minX][minZ] += toFill;
                    }
                }

                if ( waterscape.waterHeights[x][z] > 0.00001) {
                    water.setScale(vec3(1.0f, waterscape.waterHeights[x][z] / 2, 1.0));
                    water.setPosition(vec3(x, (waterscape.waterHeights[x][z] / 2) + landscape.heights[x][z], z));
                    water.render();
                }

            }
        }
    }

}

// This is our game loop where all the magic happens every frame
void GLApplication::gameLoop() {

    if (scenario == "wave")
    {
        for (int i=0; i < 49; i++)
        {
            waterscape.waterHeights[0][i] = 100.0;
        }

    }
    else if (scenario == "rise")
    {
        waterscape.waterHeights[0][0] = 0.00001;
        waterscape.waterHeights[0][49] = 0.00001;
        waterscape.waterHeights[49][0] = 0.00001;
        waterscape.waterHeights[49][49] = 0.00001;

    }
    else if (scenario == "empty")
    {
        for (int i=0; i < 49; i++)
        {
            for (int j=0; j < 49; j++)
            {
                waterscape.waterHeights[i][j] = 30.0;
            }
        }
    }
    // Loop until the user hits the Escape key or closes the window.  We created a ProcessInput function to
    // abstract the input from the main application flow so that we can make it easier for different
    // environments.  We pass in true to always keep the loop running, but this could be replaced with a
    // custom boolean variable like bGameNotOver that could be set somewhere else like a menu system.
    while ( _windowManager->processInput(true) )
    {
        TimeManager::Instance().calculateFrameRate(false);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        waterUpdate();

        land.setPosition(vec3(0, 0, 0));
        land.render();


        _windowManager->swapTheBuffers();
    }
}

// This is our own main() function which abstracts the required main() function to run this application.
int GLApplication::GLMain(std::string map, std::string scenarioType)
{
    scenario = scenarioType;
    // This calls our Initialize() function below which creates the window and triangle
    initialize(map);

    // This is our main game loop which will run until we close the window or hit Escape.
    gameLoop();

    // Return 0 for success
    return 0;
}

// This can be used to free all of our resources in the application.
GLApplication::~GLApplication()
{
    // Free the vertex buffers and array objects
    land.destroy();

    // If we have a window manager still allocated then destroy and delete it
    if ( _windowManager )
    {
        _windowManager->destroy();

        delete _windowManager;
        _windowManager = nullptr;
    }

    // If we have the camera still, delete it
    if ( _camera )
    {
        delete _camera;
        _camera = nullptr;
    }
}
