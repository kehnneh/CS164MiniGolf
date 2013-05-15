#include "BaseCamera.h"

#include <glm\gtc\matrix_transform.hpp>

static float fovy = 45.f,
			 aspect = 640.f / 480.f,
			 znear = 0.1f,
			 zfar = 10000.f;

BaseCamera::BaseCamera() {}

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
