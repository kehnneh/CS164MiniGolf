#pragma once

#include <glm\glm.hpp>

class Camera
{
private:
	glm::mat4 *matrix, *projection;

public:
	Camera();
	~Camera();
};

