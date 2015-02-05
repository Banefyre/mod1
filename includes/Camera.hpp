#ifndef _Camera_HPP_
#define _Camera_HPP_

#define PI 3.14159265358979323846264338327950288		// Define PI for usage in positioning the camera's rotations
#define GLM_FORCE_RADIANS								// Make sure GLM is using radians instead of degrees

#include <fstream>
#include <glm/glm.hpp>									// Used for the GLM math library
#include <glm/gtc/matrix_transform.hpp>					// Used for the GLM math library
#include <glm/gtx/transform2.hpp>						// Used for the GLM math library
using namespace glm;


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

// This is our bare-bones Camera class to manage user movement in our 3D scene.
// The next tutorials will add rotation and mouse support to our class.
class Camera 
{
public:

	Camera();

	// This sets and returns a perspective matrix that is build from the field of fiew, aspect ratio and near/far planes
	mat4 setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);

    // This builds and returns a rotation matrix from the yaw and pitch rotations
    mat4 getRotationMatrix();

	// This returns the current ProjectionMatrix
	mat4 getProjectionMatrix() { return _projectionMatrix; }

	// This returns the current view matrix according to the camera's position and rotation
	mat4 getViewMatrix();

	// This sets and gets the camera's position
	void setPosition(vec3 position)	{ _position = position; }
	vec3 getPosition()	{ return _position; }

	// This calculates the current view vector from the rotation matrix (hard coded for now)
	vec3 getView();

    // This returns the camera's up vector (the direction pointing up)
    vec3 getUp();

    // This returns the camera's right vector (the direction perpendicular to the view and up vectors)
    vec3 getRight();


    // This sets and gets the Yaw and Pitch rotations (in radians)
	float getYaw() { return _yaw; }
	void setYaw(float yaw)	{ _yaw = yaw; }
	float getPitch() { return _pitch; }
	void setPitch(float pitch) { _pitch = pitch; }
	
	// This sets and gets the camera's movement speed
	void setSpeed(double speed) { _speed = speed;  }
	double getSpeed() { return _speed; }

    // This gets and sets the rotation speed for the camera
    void setRotationSpeed(double speed) { _rotationSpeed = speed; }
    double getRotationSpeed() { return _rotationSpeed; }

    // This sets the pitch and yaw of our camera from the mouse x and y deltas from the last frame
    void setViewByMouse(float mouseX, float mouseY);

	// This sets the Position and the yaw and pitch rotations (in radians)
	void positionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch);

	// This will move the camera forward or backwards depending on the speed (negative for backwards)
	void moveCamera(float speed);

    // This strafes the camera left or right depending on the speed
    void strafe(float speed);


protected:

	mat4 _projectionMatrix;								// The camera's projection matrix
	vec3 _position;										// The camera's position

	float _speed = 50.0;									// The camera's speed that is used with a time slice
    // This is our rotation speed that is used with the time slice and yaw
    float _rotationSpeed = 2;
	float _yaw = 0;										// The horizontal rotation angle (in radians), y-axis
	float _pitch = 0;									// The vertical rotation angle (in radians, x-axis
    double _mouseSpeed = 0.001;							// The speed for the mouse rotations
};


#endif 

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// The camera class is used to be able to move a camera around in the world and
// take input from the user such as arrow keys, WASD keys or the mouse in a later
// tutorial.  Unlike our older tutorials, we now depend on matrices more to be
// able to calculate our camera vectors by our position and yaw/pitch rotations.
// We no longer store a view or up vector, but derive those from our rotation
// matrix which will be defined in the next tutorial.
//
// � 2000-2015 GameTutorials