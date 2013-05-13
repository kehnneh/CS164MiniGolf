#include "Camera.h"
#include "CommonUtils.h"

#include <glm\gtc\matrix_transform.hpp>

// TODO: Initialize camera! Implement arcball rotation!

Camera::Camera()
{
	projection = new glm::mat4;
	matrix = new glm::mat4;
}

void Camera::Init(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	*matrix = glm::lookAt(eye, target, up);
}

Camera::~Camera()
{
	SAFE_DELETE(projection);
	SAFE_DELETE(matrix);
}

void Camera::CreateProjectionMatrix()
{
	*projection = glm::perspective(45.f, 640.f/480.f, 0.1f, 10000.f);
}

glm::mat4 *Camera::GetMatrix()
{
	return matrix;
}

glm::mat4 *Camera::GetProjectionMatrix()
{
	return projection;
}