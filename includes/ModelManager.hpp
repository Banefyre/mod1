#ifndef _ModelManager_HPP_
#define _ModelManager_HPP_
#define GLM_FORCE_RADIANS

#include <stdio.h>										// Used for fprintf and stderr
#include <stdlib.h>										// Used for the exit() function
#include "Shader.hpp"										// Used for loading and running our shaders
#include "Camera.hpp"

// Include the GLM header files and set the namespace to GLM so we don't need to do glm:: everywhere
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

// This is our custom class to store attributes for a vertex like the x,y,z values.
// In the next tutorials we will be adding more to it like the color, UVs and normals.
class Vertex3
{
public:
    Vertex3(void) : xyz(vec3(0)), rgba(vec4(1)) {}

    // NOTE: We changed these to use glm::vec3 and glm:vec4 objects instead of arrays of floats
    vec3 xyz;											// The x,y,z position
    vec4 rgba;											// The r,g,b,a (Red, Green, Blue, Alpha) color values
};


// The Model class to handle initializing, rendering and destroying of a 3D object
class ModelManager
{
public:

	// These are created to standardize the index properties used for vertex properties.
	// In this tutorial we only use the kVertexIndex, but in later ones we will use all of them.
	static const GLuint kVertexIndex = 0;				// This is for the x,y,z vertices
	static const GLuint kColorIndex = 1;				// This is for the r,g,b,a colors
	static const GLuint kTextureIndex = 2;				// This is for the u,v texture coordinates
	static const GLuint kNormalIndex = 3;				// This is for the x,y,z normals

    // Set the scale of our model to 100% by defaul and have the deconstructor release our memory.
	ModelManager()		{ _scale = vec3(1.0f, 1.0f, 1.0f); }
	~ModelManager()	{ destroy(); }

	// Takes in a list of x,y,z vertices and vertex length to create the VBO and VAO's from,
	// as well as the text file locations for the vertex and fragment shaders to load.
	void initialize(Vertex3 vertices[], int length, std::string strVertex, std::string strFragment);
	
	// This draws the Model to the backbuffer
	void render();

    // Create the getter and setters for the model's position
    vec3  getPosition() { return _position; }
    void setPosition(vec3 position) { _position = position; }

    // Create the getter and setters for the model's rotation
    vec3  getRotation() { return _rotation; }
    void setRotation(vec3 rotation) { _rotation = rotation; }

    // Create the getter and setters for the model's scale
    vec3  getScale() { return _scale; }
    void setScale(vec3 scale) { _scale = scale; }

    // This gets and sets the camera to get access to the view and projection matrices
    Camera *getCamera() { return _camera; }
    void setCamera(Camera *pCamera) { _camera = pCamera; }



	// This cleans up the VBO and VAO's
	void destroy();

private:

	Vertex3 *_vertices;									// The list of the vertices
	GLint _verticesLength;								// The length of the vertices
	GLuint _vertexBufferId;								// The VBO Id stored by the VAO
	GLuint _vertexArrayObjectId;						// The VAO Id to bind when drawing

    vec3 _position;										// The model's position
    vec3 _rotation;										// The model's rotation
    vec3 _scale;										// The model's scale


	// Our shader object to initialize and run the shaders
	Shader _shader;

    // Add our camera object to access its matrices
    Camera *_camera;
};

#endif