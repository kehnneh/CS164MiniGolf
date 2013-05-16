#include "BaseCamera.h"

#include <glm\gtc\matrix_transform.hpp>

static float fovy = 45.f,
			 aspect = 640.f / 480.f,
			 znear = 0.1f,
			 zfar = 10000.f;

BaseCamera::BaseCamera()
{
	// Pitch is hardcoded. Maybe figure out a method to figure out what the actual pitch angle is AFTER
	// initialization, that way pitch initialization will be dynamic
	pitch = -45.f;
	yaw = 0.f;
}

BaseCamera::~BaseCamera() {}

void BaseCamera::Init()
{
	matrix = new glm::mat4;
	projection = new glm::mat4;

	CreateProjectionMatrix();
}

void BaseCamera::CreateProjectionMatrix()
{
	*projection = glm::perspective(fovy, aspect, znear, zfar);
}

void BaseCamera::SetFOV(float fov)
{
	fovy = fov;
	CreateProjectionMatrix();
}

void BaseCamera::SetScreenSize(float x, float y)
{
	aspect = x / y;
	CreateProjectionMatrix();
}

void BaseCamera::SetFarPlane(float z)
{
	zfar = z;
	CreateProjectionMatrix();
}

void BaseCamera::RotateX()
{
	// modify pitch in another method
	*matrix = glm::rotate(*matrix, pitch, glm::vec3(1.f, 0.f, 0.f));
}

void BaseCamera::RotateY()
{
	// modify yaw in another method
	*matrix = glm::rotate(*matrix, yaw, glm::vec3(0.f, 1.f, 0.f));
}

void alternateConstructMatrix()
{
	// *matrix = Rotate
}

glm::mat4 *BaseCamera::GetMatrix()
{
	return matrix;
}

glm::mat4 *BaseCamera::GetProjectionMatrix()
{
	return projection;
}