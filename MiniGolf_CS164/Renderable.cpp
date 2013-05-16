#include "Renderable.h"
#include "Shader.h"
#include "CommonUtils.h"
#include "BaseCamera.h"

#include <glm\gtc\matrix_inverse.hpp>

#define USE_FLAT_SHADING

static Shader* activeShader = 0;

Renderable::Renderable()
{
	vertices = 0;
	indices = 0;

#ifdef USE_GL_TRIANGLE_FAN
	drawMode = GL_TRIANGLE_FAN;
#else
	drawMode = GL_TRIANGLES;
#endif
}

Renderable::~Renderable()
{
	SAFE_DELETE(normalData);
	SAFE_DELETE(indexData);
	SAFE_DELETE(colorData);
	SAFE_DELETE(vertexData);
}

void Renderable::BindShader(Shader* shader)
{
	activeShader = shader;
}

void Renderable::GenerateColor()
{
	colorData = new glm::vec4[vertices];

	for (unsigned int i = 0; i < vertices; i++)
	{
		colorData[i].r = .8f;
		colorData[i].g = .0f;
		colorData[i].b = .8f;
		colorData[i].a = 1.f;
	}
}

bool Renderable::Init(glm::vec3* vertData, unsigned int numVerts)
{
	transform = new glm::mat4;


	vertices = numVerts;
	vertexData = vertData;
	TriangulateVertices();
	GenerateColor();
	GenerateNormals();
	return true;
}

//
// Ken thinks we should use GL_TRIANGLE_FAN
// instead of GL_TRIANGLES
//
void Renderable::TriangulateVertices()
{
#ifdef GL_USE_TRIANGLE_FAN
	indices = vertices;
	indexData = new unsigned int[vertices];
	for (unsigned int v = 0; v < vertices; v++)
	{
		indexData[v] = v;
	}
#else
	unsigned int nextVert = 1;
	indices = 3 * (vertices - 2);
	indexData = new unsigned int[indices];
	for (unsigned int v = 2; v < indices; v += 3)
	{
		indexData[v - 2] = 0;
		indexData[v - 1] = nextVert;
		indexData[v] = ++nextVert;
	}
#endif
}

void Renderable::GenerateNormals()
{
	// NOT for TRIANGLE_FAN
	normalData = new glm::vec3[vertices];
	memset(normalData, 0, vertices * sizeof(glm::vec3));

	for (unsigned int i = 0; i < indices; i += 3)
	{
		glm::vec3 a(vertexData[indexData[i]]),
			      b(vertexData[indexData[i + 1]]),
				  c(vertexData[indexData[i + 2]]);

		glm::vec3 result = glm::normalize(glm::cross(b - a, c - a));
		normalData[indexData[i]] += result;
		normalData[indexData[i + 1]] += result;
		normalData[indexData[i + 2]] += result;
	}

	for (unsigned int i = 0; i < vertices; i++)
	{
		glm::normalize(normalData[i]);
	}
}

void Renderable::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, activeShader->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices * 3, vertexData, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(activeShader->vertex);
	glVertexAttribPointer(activeShader->vertex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Renderable::BindColors()
{
	glBindBuffer(GL_ARRAY_BUFFER, activeShader->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices * 4, colorData, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(activeShader->color);
	glVertexAttribPointer(activeShader->color, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Renderable::BindNormals()
{
	glBindBuffer(GL_ARRAY_BUFFER, activeShader->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices * 3, normalData, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(activeShader->normal);
	glVertexAttribPointer(activeShader->normal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Renderable::BindIndices()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, activeShader->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT) * indices, indexData, GL_STATIC_DRAW);
}

void Renderable::Render(BaseCamera* c)
{
	glUniformMatrix4fv(activeShader->mat_modelTransform, 1, GL_FALSE, (GLfloat*) transform);

	glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(*transform * *c->GetMatrix()));
	glUniformMatrix3fv(activeShader->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

	BindVertices();
	BindColors();
	BindNormals();
	BindIndices();

	glDrawElements(drawMode, indices, GL_UNSIGNED_INT, NULL);
}