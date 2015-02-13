#include <gl/glew.h>
#include <GLFWManager.hpp>
#include <iostream>
#include "../includes/GLApplication.hpp"

int main(int ac, char **av)
{
    if (ac < 3 || ac > 3)
    {
        std::cout << "Usage: mod1 [map name] [scenario]" << std::endl;
        return 0;
    }

    // First create our desired WindowManager implementation so we can set it below
    GLFWManager *pWindowManager = new GLFWManager();

    // Here we initialize a camera to be used for our application, as opposed to having a global
    Camera *pCamera = new Camera();

    // Create a local instance of our GLApplication (defined in Main.cpp) and set its
    // WindowManager implementation (in this case, GLFW).
    GLApplication application;
    application.setWindowManager(pWindowManager);

    // Set the created camera as our main application camera and pass it also to our InputManager
    application.setCamera(pCamera);
    pWindowManager->getInputManager()->setCamera(pCamera);

    // Return the GLMain() defined in Main.cpp, which handles the flow of our application
    // and immediately starts our game loop.

    std::string map = std::string(av[1]);
    std::string scenario = std::string(av[2]);
    if (scenario != "empty" && scenario != "wave" && scenario != "rain" && scenario != "rise") {
        std::cout <<  "No scenario found, loading default scenario : NO WATER" << std::endl;
    }
    return application.GLMain(map, scenario);
}