#ifndef _Shader_HPP
#define _Shader_HPP

#include <string>										// Used for our STL string objects
#include <fstream>										// Used for our ifstream object to load text files
#include <glew.h>									    // Used for the OpenGL types like GLuint, GLfloat, etc.


// This is our very basic shader class that we will use to load and turn on/off our shaders
class Shader
{
public:

	// Create an empty constructor and have the deconstructor release our memory.
	Shader()	{ }
	~Shader()	{ destroy(); }

	// This loads our text file for each shader and returns it in a string
	std::string loadShaderFile(std::string strFile);

	// This loads a vertex and fragment shader from a text file (relative or full path)
	void initialize(std::string strVertexFile, std::string strFragmentFile );
	
	// This returns an ID for a variable in our shader, to be used with a Set*() function
	GLint getVariable(std::string strVariable);

	// Below are functions to set an integer, a set of floats or a matrix (float[16])
	void setInt(GLint id, int newValue)											{ glUniform1i(id, newValue);		}
	void setFloat(GLint id, GLfloat newValue)									{ glUniform1f(id, newValue);		}
	void setFloat2(GLint id, GLfloat v0, GLfloat v1)							{ glUniform2f(id, v0, v1);			}
	void setFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2)				{ glUniform3f(id, v0, v1, v2);		}
	void setFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)	{ glUniform4f(id, v0, v1, v2, v3);	}
	
	// This allows us to pass in 4x4 matrix (float array of 16) to a shader by the Id received from GetVariable()
	void setMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat *value)
	{ 
		glUniformMatrix4fv(id, count, transpose, value);
	}

	// These 2 functions turn on and off our shader, which uses the OpenGL glUseProgram() function
	void turnOn()		{	glUseProgram(_shaderProgramId);  }
	void turnOff()		{	glUseProgram(0);				}
	
	// This releases our memory for our shader
	void destroy();

private:

	// This Id stores our vertex shader information
	GLuint _vertexShaderId;

	// This Id stores our fragment shader information
	GLuint _fragmentShaderId;

	// This Id stores our program information which encompasses our shaders
	GLuint _shaderProgramId;
};

#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// In this file we have our Shader class definition, which handles the loading,
// compiling, attaching and using of shaders.
// 
// 
// � 2000-2014 GameTutorials