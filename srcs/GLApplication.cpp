#include <Landscape.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Waterscape.hpp>
#include "../includes/Cube.hpp"
#include "../includes/GLApplication.hpp" 					// Include our main header for the application
#include "../includes/Waterscape.hpp"
#include "../includes/Landscape.hpp"

ModelManager g_Model;										// Our class to handle initializing and drawing our landscape
ModelManager water;


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
void GLApplication::initialize(char *map, char *scenario)
{
    (void)scenario;
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


    //Draw a flat map, square by square. It takes 6 vertices to make a square (2 triangles).
//    int mapX=50;
//    int mapZ=50;
//    Vertex3 vertices[(mapX - 1) * (mapZ - 1) * 6];
//    int i = 0;
//
//    for (int x =0; x < 49; x++)
//    {
//        for (int z=0; z < 49; z++)
//        {
//            vertices[i].xyz = vec3(x,0,z);
//            vertices[i + 1].xyz = vec3(x+1, 0, z);
//            vertices[i + 2].xyz = vec3(x, 0 , z+1);
//
//            vertices[i + 3].xyz = vec3(x+1, 0, z);
//            vertices[i + 4].xyz = vec3(x+1, 0, z+1);
//            vertices[i + 5].xyz = vec3(x, 0 , z+1);
//
//            i+=6;
//        }
//
//    }

    //Draw our landscape;
    landscape.initMap(map);


    // Initialize the model with the vertex array and give the vertex length of 120
    g_Model.initialize(landscape.vertab, landscape.size , "Shaders/Shader.vertex", "Shaders/Shader.fragment");


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
    g_Model.setCamera(_camera);

    // Set the position of the first triangle to be at the origin
    g_Model.setPosition(vec3(0, 0, 0));

    Cube cube;
    water.initialize(cube.watervertab, 36, "Shaders/Shader.vertex", "Shaders/Shader.fragment");

    // We now pass in the camera to have access to the projection and view matrices
    water.setCamera(_camera);

    // Set the position of the first triangle to be at the origin
    water.setPosition(vec3(5, 5, 5));
}


// This is our game loop where all the magic happens every frame
void GLApplication::gameLoop()
{
    waterscape.waterHeights[0][0] = 2000.0f;


    // Loop until the user hits the Escape key or closes the window.  We created a ProcessInput function to
    // abstract the input from the main application flow so that we can make it easier for different
    // environments.  We pass in true to always keep the loop running, but this could be replaced with a
    // custom boolean variable like bGameNotOver that could be set somewhere else like a menu system.
    while ( _windowManager->processInput(true) )
    {
        TimeManager::Instance().calculateFrameRate(false);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //water algo
        for (int x = 0 ; x < landscape.getWidth() - 1 ; x++)
        {
            for (int z = 0 ; z < landscape.getHeight() - 1; z++)
            {

                if (waterscape.waterHeights[x][z])
                {


                    //check les cases autour + recupere la case la moins haute (terre+eau)

                    float minHeight = landscape.heights[x][z] + waterscape.waterHeights[x][z];
                    int minX = x;
                    int minZ = z;

                    for (int xx = x - 1; xx <= x + 1 ; xx++) {
                        for (int zz = z - 1 ; zz <= z + 1 ; zz++) {

                            if (xx >= 0 && xx < waterscape.getWidth() - 1 && zz >= 0 && zz < waterscape.getHeight() - 1) {
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
                            waterscape.waterHeights[minX][minZ] = waterscape.waterHeights[x][z];
                            waterscape.waterHeights[x][z] = 0.0f;
                        }
                        else {
                            waterscape.waterHeights[x][z] -= toFill;
                            waterscape.waterHeights[minX][minZ] += toFill;
                        }
                    }

                        water.setScale(vec3(1.0f, waterscape.waterHeights[x][z] / 2, 1.0f));
                        water.setPosition(vec3(x, (waterscape.waterHeights[x][z] / 2) + landscape.heights[x][z], z));
                        water.render();

                }
            }
        }

        g_Model.setPosition(vec3(0, 0, 0));
        g_Model.render();


        _windowManager->swapTheBuffers();
    }
}

// This is our own main() function which abstracts the required main() function to run this application.
int GLApplication::GLMain(char *map, char *scenario)
{
     std::cout << map << std::endl;
    // This calls our Initialize() function below which creates the window and triangle
    initialize(map, scenario);

    // This is our main game loop which will run until we close the window or hit Escape.
    gameLoop();

    // Return 0 for success
    return 0;
}

// This can be used to free all of our resources in the application.
GLApplication::~GLApplication()
{
    // Free the vertex buffers and array objects
    g_Model.destroy();

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
