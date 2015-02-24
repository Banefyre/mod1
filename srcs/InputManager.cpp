//***********************************************************************//
//																		 //
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 //
//                                                                       //
//		$Program:		Camera											 //
//																		 //
//		$Description:	Moves a camera in 3D space from user input		 //
//																		 //
//***********************************************************************//

#include "../includes/InputManager.hpp"
#include "../includes/TimeManager.hpp"


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

// This takes in a code and depending on the value moves the camera
void InputManager::keyPressed(InputCodes code)
{
	// If there isn't a camera specified, just return
	if ( _camera == nullptr )
		return;

	// Depending on the code, move the camera back or forward fixed by a speed and time slice
	// to make sure the movement is the same on anyone's computer regardless of the speed.

    if (code == Up || code == W || code == w)
    {
        _camera->moveCamera(_camera->getSpeed() * TimeManager::Instance().deltaTime);
    }
    else if (code == Down || code == S || code == s)
    {
        _camera->moveCamera(-1 * _camera->getSpeed() * TimeManager::Instance().deltaTime);
    }
    else if (code == Left || code == A || code == a)
    {
        _camera->strafe(-1 * _camera->getSpeed() * TimeManager::Instance().deltaTime);
    }
    else if (code == Right || code == S || code == s)
    {
        _camera->strafe(_camera->getSpeed() * TimeManager::Instance().deltaTime);
    }

	/*switch ( code )
	{
		// If the user moves up, move the camera up along the view vector
		case Up: case W: case w:
			_camera->moveCamera(_camera->getSpeed() * TimeManager::Instance().deltaTime);
			break;
		// If the user moved down, move the camera down along the view vector
		case Down: case S: case s:
			_camera->moveCamera(-1 * _camera->getSpeed() * TimeManager::Instance().deltaTime);
			break;		
	}*/
}


void InputManager::mouseMoved(float mouseX, float mouseY)
{
    // Return if we don't have a valid camera assigned
    if ( _camera == nullptr )
        return;

    // Have our manager send the mouse x and y deltas to our camera to process the rotations
    _camera->setViewByMouse(mouseX, mouseY);
}

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// The InputManager allows us to abstract the input away from the WindowManager so
// it wouldn't matter if we used GLFW, Win32, SDL, Glut, etc., and just sends standardized
// input codes from the WindowManager to this this class and then to the camera.
// In this tutorial we just process the UP and DOWN arrow keys (or W,S) to move the
// camera back and forth, but later it will handle the left and right rotations and
// even movement by the mouse and strafing.