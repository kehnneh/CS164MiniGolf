#include "BaseCamera.h"

#include <glm\core\func_trigonometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

static float fovy = 45.f,
			 aspect = 640.f / 480.f,
			 znear = 0.1f,
			 zfar = 10000.f;

static const float pitch_limit = 90.f;
static const float scale = 6.f;

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

void BaseCamera::ConstructMatrix()
{
	//*matrix = glm::lookAt(eye, glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
	*matrix = glm::lookAt(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

	//Translate();
	RotateX();
	RotateY();
	Translate();
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

void BaseCamera::IncYaw(float amt)
{
	yaw += amt;

	if (yaw > 360.f)
	{
		yaw -= 360.f;
	}
	else if (yaw < 0.f)
	{
		yaw += 360.f;
	}
}

void BaseCamera::IncPitch(float amt)
{
	pitch += amt;

	if (pitch > pitch_limit)
	{
		pitch = 89.9f;
	}
	else if (pitch < -pitch_limit)
	{
		pitch = -89.9f;
	}
}

void BaseCamera::RotateX()
{
	*matrix = glm::rotate(*matrix, pitch, glm::vec3(1.f, 0.f, 0.f));
}

void BaseCamera::RotateY()
{
	*matrix = glm::rotate(*matrix, yaw, glm::vec3(0.f, 1.f, 0.f));
}

void BaseCamera::Translate()
{
	// Translate according to coordinate view frame!
	glm::vec4 translate((*matrix)[0].z, (*matrix)[1].z, (*matrix)[2].z, 0.f);
	//translate.x = glm::cos(glm::radians(yaw)) * scale;
	//translate.z = glm::sin(glm::radians(yaw)) * scale;
	//translate.y = 5.f;
	//translate += eye.x * (*matrix)[0];
	//translate += eye.y * (*matrix)[1];
	//translate += -5.f * (*matrix)[2];
	translate *= 5.f;
	*matrix = glm::translate(*matrix, -glm::vec3(translate));
	//*matrix = glm::translate(*matrix, -eye);
	//*matrix = glm::translate(-eye) * *matrix;
}

void BaseCamera::Tick()
{
	ConstructMatrix();
}

glm::mat4 *BaseCamera::GetMatrix()
{
	return matrix;
}

glm::mat4 *BaseCamera::GetProjectionMatrix()
{
	return projection;
}