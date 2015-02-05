//***********************************************************************//
//																		 //
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 //
//                                                                       //
//		$Program:		Camera											 //
//																		 //
//		$Description:	Moves a camera in 3D space from user input		 //
//																		 //
//***********************************************************************//

#include <iostream>
#include "../includes/Camera.hpp"


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

/*
This is our new Camera class which stores a camera's Position, Yaw and Pitch rotations.
Unlike our legacy OpenGL tutorials, this camera class doesn't store the view and up vector,
but will use the Yaw (y-axis rotation) and Pitch (x-axis rotation) to calculate them on the fly.
We also added the creation of the projection matrix into our Camera class with SetPerspective().
In this first tutorial in our camera tutorial series, we just use the MoveCamera() function to
move the camera along it's default view vector, which is looking down the negative z-axis.
*/

// Initialize the camera to have a position at the origin
Camera::Camera()
{
	// Set the default position for the camera to the origin
	_position = vec3(0.0, 0.0, 0.0);
}


// This sets and returns the camera's perspective matrix from a field of view (in radians), aspect ratio 
// and the near and far planes which cull the geometry outside our desired viewing distance.
mat4 Camera::setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	// Create the projection matrix with GLM's perspective function, replacing gluPerspective.
	_projectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);

	return _projectionMatrix;
}


// This function sets the camera's position and rotation values
void Camera::positionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch)
{
	// Assign our camera variables
	_position = vec3( positionX, positionY, positionZ );
	_yaw = yaw;
	_pitch = pitch;
}

// This builds and returns a rotation matrix from the yaw and pitch rotations
mat4 Camera::getRotationMatrix()
{
    // To create a rotation matrix from our Yaw and Pitch angles, we just need to
    // first create a blank identity matrix, the call the glm::rotate() function
    // to pass in that new matrix with the angle and axis to rotate on.  In the case
    // of Pitch, this is a rotation along the x-axis so we use vec3(1, 0, 0).
    // For Yaw, this is a rotation along the y-axis so we use vec3(0, 1, 0).
    // The rotation matrix can now be used to calculate the rest of our camera details.

    // Create an identity matrix
    mat4 rotationMatrix(1.0f);

    // Add the Pitch rotation along the x-axis
    rotationMatrix = rotate(rotationMatrix, _pitch, vec3(1, 0, 0));

    // Add the Yaw rotation along the y-axis
    rotationMatrix = rotate(rotationMatrix, _yaw, vec3(0, 1, 0));

    // Return the final rotation matrix that stores our camera rotations
    return rotationMatrix;
}


// This returns the camera's view matrix that is used to pass to our shaders
mat4 Camera::getViewMatrix()
{
    // To create a view matrix you multiply the camera's rotation matrix by the inverse
    // of the translation matrix.  The rotation matrix contains all the rotations for
    // our Yaw and Pitch, and the translation matrix contains the Position of the camera.
    // This matrix will be used to pass into our shaders from our models to tell OpenGL
    // what we are looking at so it knows what and where to draw on the screen.
    // In the last tutorial we just returned the inverse of the translation matrix,
    // but now we combine the rotation and the translation matrix to give a final matrix.
    return getRotationMatrix() * inverse(translate(mat4(), _position));
}


// This returns the current view vector (the direction the camera is looking) from the rotation matrix
vec3 Camera::getView()
{
    // Since we don't store a view vector, we need to calculate the view vector by taking
    // the inverse of our rotation matrix multiplied by a vector looking down the negative
    // z-axis.  By taking the inverse of our rotation matrix and initial view vector, this
    // essentially gives us the vector that would have been used to create the current matrix.
    // So this essentially gives us a unit vector (length of 1) that represents the direction
    // the camera is looking at.
    vec4 viewVector = inverse(getRotationMatrix()) * vec4(0, 0, -1, 1);

    // We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
    return vec3(viewVector);
}


// This returns the camera's up vector (the direction pointing up) from the rotation matrix
vec3 Camera::getUp()
{
    // Just like we abstracted the view vector from our rotation matrix, we do the same
    // thing to get the up vector but instead change the vector to a vector pointing up.
    // By taking the inverse of the rotation matrix multiplied by a default up vector,
    // it will give us the current up vector of the camera.  The up vector will always
    // be vec3(0, 1, 0) until our next tutorial since we aren't looking up or down yet.
    vec4 upVector = inverse(getRotationMatrix()) * vec4(0, 1, 0, 1);

    // We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
    return vec3(upVector);
}

// This returns the camera's right vector (the direction pointing perpendicular to the view and up vector)
vec3 Camera::getRight()
{
    // Calculate the right vector by taking the inverse of the rotation matrix multiplied by a
    // default right vector.
    vec4 rightVector = inverse(getRotationMatrix()) * vec4(1, 0, 0, 1);

    // We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
    return vec3(rightVector);
}

// This will strafe the camera left or right depending on the speed
void Camera::strafe(float speed)
{
    // Get our normalized right vector (The direction perpendicular to our view)
    vec3 rightVector = getRight();

    // Move our camera position right or left along the right vector
    _position.x += rightVector.x * speed;		// Add our acceleration to our position's X
    _position.z += rightVector.z * speed;		// Add our acceleration to our position's Z
}
// This will move the camera forward or backward depending on the speed
void Camera::moveCamera(float speed)
{
    // In order to move the camera, we first need to get the direction that the camera is
    // facing.  We have this from our GetView() function.  Until we get rotations in the
    // next tutorial, we just hard code our view vector to look down the negative z-axis.

    // *SIDE NOTE* If you were storing a position and view location like in our old OpenGL
    // tutorials, you would need to take the view (the location we are looking) and
    // subtract the camera's Position from it.  That will give us a view vector (direction)
    // that the camera is looking.  You would need to then normalize() that vector to make
    // sure it has a length of 1 to make our calculations for our speed consistent no
    // matter how far away the view location is from the camera.

    // Get our normalized view vector (The direction we are facing)
    vec3 viewVector = getView();

    // Now that we have the direction the camera is facing, we will move the position
    // along that vector with a consistent speed.  The speed is consistent because we
    // multiply the camera's speed by a time slice from our InputManager.  That way it
    // doesn't matter how fast or slow your computer is, it will move at the same speed.
    // If the speed is positive, then the camera will move forward, and if it's negative
    // the camera will move backwards. Notice we don't move the y value of the camera's
    // position so the camera doesn't come off the ground when they look up.  This would
    // make sense if we were flying something or in space perhaps though.

    // Move our camera position forward or backward along the view vector
    _position.x += viewVector.x * speed;		// Add our acceleration to our position's X
    _position.y += viewVector.y * speed;		// Add our acceleration to our position's Y
    _position.z += viewVector.z * speed;		// Add our acceleration to our position's Z

   // std::cout << "pos x : " << this->_position.x << "pos y : " << this->_position.y << "pos z : " << this->_position.z << "pitch : " << this->_pitch << "yaw : " << this->_yaw << std::endl;
}

// This sets the pitch and yaw of our camera from the mouse x and y deltas from the last frame
void Camera::setViewByMouse(float xOffset, float yOffset)
{
    // Rotate the yaw by the mouse's x offset, multiplied by a sensitivity speed setting
    _yaw += xOffset * _mouseSpeed;

    // Rotate the pitch by the mouse's y offset, multiplied by a sensitivity speed setting
    _pitch += yOffset * _mouseSpeed;

    // If the yaw goes above 360 degrees (2 PI in radians) then set it back to 0 so
    // we keep the rotation between 0 and 360 degrees.  This is just a preference of working
    // with 0-360 instead of 570+, etc...
    if ( _yaw > 2 * PI )
        _yaw = 0;

    // Cap the yaw between 0 and 360
    if ( _yaw < 0 )
        _yaw = 2 * PI;

    // Let's cap the pitch to 75 degrees up and -75 degrees down.  This makes it so you don't
    // have the camera flipping upside down if you look to far up or down.  There could be a
    // reason though to want to allow that, especially in a scripting camera.  This also can
    // avoid the "gimbal lock" issue where if you look straight up or down it wigs out.  This
    // can be avoided with quaternion rotations instead of euler rotations too.
    if ( _pitch > radians(75.0f) )
        _pitch = radians(75.0f);
    if ( _pitch < radians(-75.0f) )
        _pitch = radians(-75.0f);
}

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// This is our Camera class which controls the user's view in the 3D world.  In
// this tutorial we only show how to move the camera back and forth along the
// z-axis, but in the next tutorial we go over rotations and start making it be
// a useful camera class.  We will now handle all projection and view matrices 
// inside this class going forward.  This way our Models can just take a camera
// instance and get the matrices from there instead of passing them in each frame.
// As a reminder, this class is super bare bones and we will be building on top
// of it throughout the next tutorials in the camera series.
//
// We are using the glm library for all of our 3D math functions, so the inverse()
// function comes in handy.  Taking the inverse of a matrix is the same idea as
// reciprocal of a number, like the reciprocal of 100 is 1/100.  Since you don't
// divide with matrices, you create an inverse of a matrix.  If you were to
// multiply a matrix by it's inverse it returns the identity matrix.  As you will
// see in the next tutorial we use the inverse to derive the view and up vector
// from the inverse of the rotation matrix.
//
// �2000-2015 GameTutorials