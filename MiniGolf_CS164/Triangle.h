#pragma once

#include <glm\glm.hpp>

class Triangle
{
private:
	glm::vec3 vertices[3], normal;

	void CalculateNormal();

public:
	Triangle();
	~Triangle();

	void SetVertices(glm::vec3 *verts);
};

