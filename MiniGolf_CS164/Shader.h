#pragma once

#include <gl\glew.h>
#include <gl\freeglut.h>

class Shader
{
public:
	GLint
		// The OpenGL Object that represents the OGL program
		program,
		// The OGL object that determines where the camera's matrix gets pushed to
		mat_camera,
		// The OGL object that determines where the model's transformation matrix gets pushed to
		mat_modelTransform,
		// The OGL object that determines where the camera's projection matrix gets pushed to
		mat_projection,
		// The OGL object that determines where the normal matrix gets pushed to
		mat_normal,
		// The next four determine where data gets sent on a per-vertex basis
		vertex,
		color,
		normal,
		// The sun is where the global light source comes from
		sun;

	GLuint
		// Vertex Array Objects for OGL. Data gets pushed into these.
		vertexBuffer,
		colorBuffer,
		normalBuffer,
		indexBuffer;

	Shader();
	~Shader();

	bool Init(char* vsFile, char* fsFile);
	void Enable();

private:
	GLint SetShaderSource(char* filename, GLenum type);
	void PrintLog(char* label, GLint obj);
};

