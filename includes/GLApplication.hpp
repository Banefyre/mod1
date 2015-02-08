#ifndef _GLAPPLICATION_HPP_
#define _GLAPPLICATION_HPP_

#include "WindowManager.hpp"					// Include our WindowManager to handle the application window
#include "ModelManager.hpp"						// Include our Model class to draw the setup and draw the triangle
#include "TimeManager.hpp"                      //Include TimeManager class for time slices

// This is our main application class that handles orchestrating the init, game loop and cleanup
// of the application.  This is defined in Main.cpp and should be the first place you look for
// the tutorial instructions when opening this tutorial.  The GLFWManager.cpp will have the
// entry point function (main() for a console application, WinMain() for a Win32 application).
// The entry point then creates an instance of GLApplication and runs the GLMain() function.
class GLApplication
{
public:

    // The width and height of the application
    static const int screenWidth = 1024;
    static const int screenHeight = 768;

    // Create a default constructor and deconstructor which cleans up
    GLApplication();
    ~GLApplication();
    GLApplication(GLApplication const & src);
    GLApplication&operator=(GLApplication const & rhs);

    // This is the main function for our application, which is called by the main() function
    // in the WindowManager.cpp file.  This helps abstract out the environments entry point.
    int GLMain(char *map, char *scenario);

    // This gets and sets the window manager for the application.  This should be set right
    // after the GLApplication is created in the main() function.
    WindowManager *getWindowManager()const;
    void setWindowManager(WindowManager *pWindowManager) { _windowManager = pWindowManager; }

    // We now pass in a Camera object to our application
    Camera *getCamera()const;
    void setCamera(Camera *pCamera) { _camera = pCamera; }

    // This initializes the application
    void initialize(char *map, char *scenario);

    // This runs the game loop and only quits when the user hits Escape or closes the window
    void gameLoop();


private:

    // Our abstract window manager to create the window and manage input, which should be
    // environment agnostic.  Our main application shouldn't know if it's Win32 or GLFW.
    // This is instantiated and set in GLFWManager.cpp in the main() function.
    WindowManager *_windowManager;
    Camera        *_camera;
};

#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES *
//
// In this file we defined our main GLApplication class which runs the tutorial.
//
//
// � 2000-2014 GameTutorials