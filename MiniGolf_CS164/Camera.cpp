#include "Camera.h"
#include "CommonUtils.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

// TODO: Initialize camera! Implement arcball rotation!

Camera::Camera()
{
	projection = new glm::mat4;
	matrix = new glm::mat4;
}

Camera::~Camera()
{
	SAFE_DELETE(projection);
	SAFE_DELETE(matrix);
}

void Camera::Init(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	eyePos = eye;
	lookAt = target;
	this->up = up;

	ConstructMatrix();
	CreateProjectionMatrix();
}

void Camera::CreateProjectionMatrix()
{
	*projection = glm::perspective(45.f, 640.f/480.f, 0.1f, 10000.f);
}

void Camera::ConstructMatrix()
{
	*matrix = glm::lookAt(eyePos, lookAt, up);
}

void Camera::ArcRotate(float amt, glm::vec3 axis)
{
	glm::vec3 cfv(eyePos - lookAt);
	cfv = glm::vec3(glm::rotate(amt, axis) * glm::vec4(cfv, 0.f));
	cfv += lookAt;
	eyePos = cfv;
	ConstructMatrix();
}

void Camera::SetPosition(glm::vec3 eye)
{
	eyePos = eye;
	ConstructMatrix();
}

void Camera::SetTarget(glm::vec3 target)
{
	lookAt = target;
	ConstructMatrix();
}

glm::mat4 *Camera::GetMatrix()
{
	return matrix;
}

glm::mat4 *Camera::GetProjectionMatrix()
{
	return projection;
}

glm::vec3 *Camera::GetEyePosition()
{
	return &eyePos;
}