#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

class Shader;
class BaseCamera;

class Renderable
{
protected:
	unsigned int vertices, indices;

	// The matrix doesn't do anything right now, since the vertices are hard coded. Vertices need to be abstracted such that
	// the transform matrix represents the renderable's orientation. For tiles, the transform matrix should be the center of the tile
	glm::mat4* transform;

	glm::vec4* colorData;
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

	void Render(BaseCamera* c);
	
	static void BindShader(Shader* s);
};
