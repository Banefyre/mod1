//***********************************************************************//
//																		 //
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 //
//																		 //
//		$Program:		First OpenGL Program							 //
//																		 //
//		$Description:	Init OpenGL 4 and draw a triangle to the screen	 //
//																		 //
//***********************************************************************//

#include "../includes/ModelManager.hpp"

/*
The Model class is used to manage the functionality of taking in vertex data to render an object
in 3D.  Simply, this has an Initialize(), Render() and Destroy() function.  In this tutorials, we will
just be rendering a single triangle, which has 3 points that are passed into the Initialize() function.
This will grow in the next tutorials when we start working with Matrices and more complex items.
*/

// This takes in an array of Vertex3's and the length of the array, which generates the Vertex Buffer
// Object and Vertex Array Object for the model.  It also passes in the text file locations for the
// shaders that will be loaded and compiled to render the triangle.
void ModelManager::initialize(Vertex3 vertices[], GLint length, std::string strVertex, std::string strFragment)
{
	// Create and compile our GLSL vertex and fragment shaders from the shader text files passed
	// in.  Please refer to Shader.cpp to see how these shaders are loaded, compiled then assigned.
	_shader.initialize(strVertex, strFragment);

	// Store the list of vertices and the length in our member variables
	_vertices = vertices;
	_verticesLength = length;

	// This function gets the last error that happened from OpenGL, after the last time this
	// function was called.  So by calling it now, we reset the errors and then call it below again.
	GLenum ErrorCheckValue = glGetError();
	
	// This is where we create our Vertex Array Object (VAO), which saves the state and property information
	// about the Vertex Buffer Object (which stores the vertices in a buffer to pass to the GPU).
	// glGenVertexArrays() sends back a new unique unsigned number that represents the VAO.  Once we
	// receive the newly created VAO index we need to bind it to tell OpenGL we are using is right away.
	// This can generate many VAO's, but we just need one so we just pass in a single GLuint and just say
	// that we want to 1 returned.
	glGenVertexArrays(1, &_vertexArrayObjectId);
	glBindVertexArray(_vertexArrayObjectId);

	// Now we need to create our Vertex Buffer Object (VBO) which stores a buffer of all the vertices,
	// which can then be quickly passed to our video card's GPU to render them every frame.  Similar to
	// generating the VAO, we need to also get a unique number for the VBO with glGenBuffers, which we
	// tell it that we want 1 number back.  We then immediately bind the buffer to memory to tell OpenGL
	// we want to be working with that newly created buffer going forward.  GL_ARRAY_BUFFER tells OpenGL
	// that this buffer is a standard array of data instead of an indexed array with GL_ELEMENT_ARRAY_BUFFER.
	// Indexed arrays works as long as you aren't doing texture coordinates, which can't be shared so
	// you end up having to pass all the duplicated vertices in anyways if you want texture mapping.
	glGenBuffers(1, &_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);

	// The next steps is actually storing the list of vertices in our buffer.  We use the same target
	// GL_ARRAY_BUFFER as what we bound to above, and then the length of the buffer, then the actual
	// buffer which is the vertices passed in, then a "hint" to OpenGL to tell it if it will be a static
	// buffer or will be changing (DYNAMIC).  We will always just choose STATIC in our case.  This "hint"
	// just helps OpenGL know if the data will be changing often so it knows how to optimize the usage.
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0]) * length, _vertices, GL_STATIC_DRAW);

	// Here is where we tell OpenGL what the format each vertex is within our buffer.  In our case, we
	// have 3 floats. In this tutorial we only have vertices, but if we had colors and other things like
	// texture coordinates and normals, we would need to call this function for each attribute.  The
	// next tutorial on colors will go over this.  First we pass in the index used to refer to the
	// attribute, in our case, the vertices, and I pass in a constant value kVertexIndex which is 0.
	// I created a constant for each type of attribute we will use, defined in the Model.h file.
	// Later when we render we need to turn on this index with glEnableVertexAttribArray().  The next
	// parameters are the number of floats which is 3 for the xyz, then the format (GL_FLOAT), then
	// FALSE since we don't need OpenGL to normalize our fixed-point data, then the size in bytes each
	// attribute is, then a pointer to the location the attribute is within the Vertex3 class.  The
	// default is 0, which means that it's the first property in the class, which xyz is.  In the
	// next tutorial you will see how we need to pass in a pointer to the location of the color
	// attribute within the Vector3 class.
	glVertexAttribPointer(kVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), 0);


    // We now need to add the color attributes to our Vertex Array Object and Vertex Buffer Object.
    // This takes an index to be referenced in the vertex shader(kColorIndex = 1), the number of
    // floats(4 for r, g, b, a), the type which is a GL_FLOAT, we don't want it normalized so GL_FALSE,
    // the size of a single Vertex3 object, and then a void pointer to the start of the location
    // within the Vertex3 class to the rgba property, which is right after the xyz variable.  By
    // giving a pointer to the size of the xyz variable, we give the offset in bytes into the class.
    glVertexAttribPointer(kColorIndex, 4, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), (GLvoid*)sizeof(_vertices[0].xyz));

	// Now check to see if any errors happened in this function, which saves us tons of time instead
	// of trying to figure out why our screen is black and we would have no idea why.
	ErrorCheckValue = glGetError();

	// If there was an error found, print it to the screen and close the OpenGL window.
	if ( ErrorCheckValue != GL_NO_ERROR )
	{
		// Use gluErrorString(ErrorCheckValue) if you want to get the string value of the
		// error, but I removed this since Mac OSX 10.9 (Mavericks) deprecated this function.
		fprintf(stderr, "ERROR: Could not create a VAO and VBO with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
}


// This is the function that will actually render the model to the backbuffer, usually every frame
// if called in the GameLoop() function in Main.cpp.  
void ModelManager::render()
{
	// This turns our shader on before we tell OpenGL to render the triangle.
	_shader.turnOn();

    // Grab the view and projection matrices from the current camera
    mat4 projectionMatrix = _camera->getProjectionMatrix();
    mat4 viewMatrix = _camera->getViewMatrix();

    // Create the Model Matrix with the current position.  The first parameter is the matrix to
    // start with, which mat4(1.0f) gives us an Identity Matrix, and the second parameter is the
    // Position.  The translate() function is a GLM function which returns a transform matrix.
    mat4 modelMatrix = translate(mat4(1.0f), _position);

    // Similar to the Position above, we do the same for the Scale.  This needs to be (1,1,1) if
    // we don't want the size to change at all, and be 100% of the original size.  We set the scale
    // to vec3(1,1,1) in the Model constructor.
    modelMatrix = scale(modelMatrix, _scale);

    // Add any rotation to the Model Matrix for each axis.  The rotation value is in degrees, and
    // we pass in the axis we want to rotate on for each value.
    modelMatrix = rotate(modelMatrix, _rotation.x, vec3(1, 0, 0));	// x-axis
    modelMatrix = rotate(modelMatrix, _rotation.y, vec3(0, 1, 0));	// y-axis
    modelMatrix = rotate(modelMatrix, _rotation.z, vec3(0, 0, 1));	// z-axis

    // Get the variables from the shader for each matrix
    GLint modelMatrixId = _shader.getVariable("modelMatrix");
    GLint viewMatrixId = _shader.getVariable("viewMatrix");
    GLint projectionMatrixId = _shader.getVariable("projectionMatrix");

    // Set the model, view and projection matrix for the uniform matrices in the Vertex Shader.
    // To get at a GLM mat4 value, we use the address of the first item [0][0].
    _shader.setMatrix4(modelMatrixId, 1, false, &modelMatrix[0][0]);
    _shader.setMatrix4(viewMatrixId, 1, false, &viewMatrix[0][0]);
    _shader.setMatrix4(projectionMatrixId, 1, false, &projectionMatrix[0][0]);


	// First we want to tell OpenGL with VAO is going to be used for rendering.  SInce there could
	// be other Model objects being rendered with their own VAO, we need to set it every time we render.
	glBindVertexArray(_vertexArrayObjectId);

	// Before drawing our model, we need to specify the attribute index that will be used when drawing
	// this model, which in our case is just the vertex attribute (0).  Later we will also enable color.
	glEnableVertexAttribArray(kVertexIndex);

    // Tell OpenGL to enable our color information within the shaders
    glEnableVertexAttribArray(kColorIndex);

	// glDrawArrays() is the function that actually tells OpenGL to draw the triangles from our VBO,
	// according to the VAO which stores the state and glVertexAttribPointer() properties used when we 
	// created the VBO in our Initialize() function.  We first pass in GL_TRIANGLES since we are rendering
	// triangles, then a starting position of 0 within the array since we want to render all of the
	// vertices from the the begiining of the array, and then finally the amount of vertices to draw.
	glDrawArrays(GL_TRIANGLES, 0, _verticesLength);

    // Disable the color index
    glDisableVertexAttribArray(kColorIndex);

	// Now we do our cleanup, which is to disable the current vertex attribute for our VAO/VBO.
	glDisableVertexAttribArray(kVertexIndex);

	// Next, let's reset the current VAO binding to 0, which clears out any binding. This isn't necessary
	// since the next time a glBindVertexArray() would be called from another Model it will override 
	// the current one, but just to show how to clear a VAO binding I added this for those interested.
	glBindVertexArray(0);

	// This turns off the shader so that other objects rendered after this won't be using this shader.
	// The idea is that this is how you would turn on and off shaders for different objects being drawn
	// with their own shaders. Say for instance, one character might have a cartoon-rendered look and
	// another would have a more realistic rendering that requires completely separate shaders.
	_shader.turnOff();
}


// This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
void ModelManager::destroy()
{
	// If we have a valid vertex buffer, reset it's binding, delete it and clear the property
	if ( _vertexBufferId )
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_vertexBufferId);
		_vertexBufferId = 0;
	}

	// If we have a valid vertex array, reset it's binding, delete it and clear the property
	if ( _vertexArrayObjectId )
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &_vertexArrayObjectId);
		_vertexArrayObjectId = 0;
	}

    // Be sure to stop pointing to the camera object
    _camera = nullptr;

	// Release the memory for the compiled shaders
	_shader.destroy();
}


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// Now you can see how to initialize and draw with a Vertex Buffer Object (VBO) 
// and a Vertex Array Object (VAO), which replaces the old way of using glBegin()
// and glEnd() in OpenGL 2.0 and below.  OpenGL 3.0 is the version where it changed.
// Instead of using glBegin()/glEnd(), we now need to use glDrawArrays() which draws
// from the buffers stored on the video card.
// 
// We also went over in this file about how to use our Shader class to initialize,
// then turn on and off our shader when rendering.  Checkout Shader.cpp for more
// details on how the shaders are loaded, compiled and assigned.
//
// The next tutorial will go over adding the ability to pass in colors to the 
// shaders, which will require us to use an extra glVertexAttribPointer() call to
// tell OpenGL where the color information is within our buffer.
// 
// � 2000-2014 GameTutorials