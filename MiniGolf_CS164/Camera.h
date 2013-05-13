#pragma once

#include <glm\glm.hpp>

class Camera
{
private:
	glm::mat4 *matrix, *projection;

	void CreateProjectionMatrix();

public:
	Camera();
	~Camera();

	void Init(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

	glm::mat4* GetMatrix();
	glm::mat4* GetProjectionMatrix();
};

