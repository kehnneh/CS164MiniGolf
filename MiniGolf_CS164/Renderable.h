#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

class Shader;
class Camera;

class Renderable
{
protected:
	unsigned int vertices, indices;

	glm::vec4* colorData;
	glm::mat4* transform;
	glm::vec3* vertexData;
	glm::vec3* normalData;
	unsigned int* indexData;

private:
	GLenum drawMode;

	void BindVertices();
	void BindNormals();
	void BindIndices();
	void BindColors();

	void TriangulateVertices();
	void GenerateNormals();
	virtual void GenerateColor();

public:
	Renderable();
	~Renderable();

	bool Init(glm::vec3* vertData, unsigned int numVerts);

	void Render(Camera* c);
	
	static void BindShader(Shader* s);
};
