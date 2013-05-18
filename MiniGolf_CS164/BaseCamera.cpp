#include "BaseCamera.h"
#include "CommonUtils.h"

#include <glm\core\func_trigonometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

static float fovy = 45.f,
			 aspect = 640.f / 480.f,
			 znear = 0.1f,
			 zfar = 10000.f;

static const glm::vec3 ORIGIN(0.f, 0.f, 0.f);
static const glm::vec3 DEFAULTDIR(0.f, 0.f, 1.f);
static const glm::vec3 XAXIS(1.f, 0.f, 0.f);
static const glm::vec3 YAXIS(0.f, 1.f, 0.f);
static const glm::vec3 ZAXIS(0.f, 0.f, 1.f);

static const float pitch_limit = 90.f;
static const float backup = -5.f;

// Performs memory allocation!
void BaseCamera::Init()
{
	matrix = new glm::mat4;
	projection = new glm::mat4;
	_pipeline.push_back(&BaseCamera::InitMatrix);
	_pipeline.push_back(&BaseCamera::RotateX);
	_pipeline.push_back(&BaseCamera::RotateY);
	_pipeline.push_back(&BaseCamera::TranslateToTarget);
	_pipeline.push_back(&BaseCamera::ThirdPerson);
}

void BaseCamera::DeInit()
{
	SAFE_DELETE(matrix);
	SAFE_DELETE(projection);
}

void BaseCamera::ProjectionMatrix() { *projection = glm::perspective(fovy, aspect, znear, zfar); }

void BaseCamera::InitMatrix() {	*matrix = glm::lookAt(ORIGIN, DEFAULTDIR, up); }

// Grab the Camera's z-axis vector and move negatively along it
void BaseCamera::ThirdPerson() { *matrix = glm::translate(*matrix, (*matrix)[0].z * backup, (*matrix)[1].z * backup, (*matrix)[2].z * backup); }

// Translates the camera such that it is positioned at the fixed point
// Here, target is the fixed point to rotate about
void BaseCamera::TranslateToTarget() { *matrix = glm::translate(*matrix, target); }

void BaseCamera::Matrix()
{
	for (std::vector<void(BaseCamera::*)()>::iterator it = _pipeline.begin(); it != _pipeline.end(); ++it)
	{
		(this->*(*it))();
	}
}

// Checks to see if the particular matrix needs updating, and then updates it
// and specifies that the matrix does not need updating. Prevents the matrix
// from being re-generated on frames when it doesn't change.
// Ken made a funny, this function makes the matrix if it needs to be re-generated
void BaseCamera::Maketrix(bool& update, void (BaseCamera::*maketrix)(void))
{
	if (update)
	{
		(this->*maketrix)();
		update = false;
	}
}

// Get's called every time Kengine::Tick() is called
void BaseCamera::Tick()
{
	Maketrix(bProjectionUpdate, &BaseCamera::ProjectionMatrix);
	Maketrix(bMatrixUpdate, &BaseCamera::Matrix);
}

void BaseCamera::SetFOV(float fov)
{
	fovy = fov;
	bProjectionUpdate = true;
}

void BaseCamera::SetScreenSize(float x, float y)
{
	aspect = x / y;
	bProjectionUpdate = true;
}

void BaseCamera::SetFarPlane(float z)
{
	zfar = z;
	bProjectionUpdate = true;
}

// Increments the Yaw (Y-Rotation) by the specified amount in degrees
void BaseCamera::IncYaw(float degrees)
{
	yaw += degrees;

	if (yaw > 360.f)
	{
		yaw -= 360.f;
	}
	else if (yaw < 0.f)
	{
		yaw += 360.f;
	}

	bMatrixUpdate = true;
}

// Increments the Pitch (X-Rotation) by the specified amount in degrees
void BaseCamera::IncPitch(float degrees)
{
	pitch += degrees;

	if (pitch > pitch_limit)
	{
		pitch = 89.9f;
	}
	else if (pitch < -pitch_limit)
	{
		pitch = -89.9f;
	}

	bMatrixUpdate = true;
}

// Rotates the Camera around the X-Axis by the Camera's Pitch value
void BaseCamera::RotateX() { *matrix = glm::rotate(*matrix, pitch, XAXIS); }

// Rotates the Camera around the Y-Axis by the Camera's Yaw value
void BaseCamera::RotateY() { *matrix = glm::rotate(*matrix, yaw, YAXIS); }
//*matrix = glm::rotate(yaw, YAXIS) * *matrix; // free look!

// Translates along the Camera's z-axis.
void BaseCamera::MoveForward(float distance)
{
	target.x += (*matrix)[0].z * distance;
	target.y += (*matrix)[1].z * distance;
	target.z += (*matrix)[2].z * distance;

	eye.x += (*matrix)[0].z * distance;
	eye.y += (*matrix)[1].z * distance;
	eye.z += (*matrix)[2].z * distance;

	bMatrixUpdate = true;
}

// Translates along the Camera's x-axis
// 'Right' in the lookAt matrix is actually defined as 'Left'
void BaseCamera::MoveLeft(float distance)
{
	target.x += (*matrix)[0].x * distance;
	target.y += (*matrix)[1].x * distance;
	target.z += (*matrix)[2].x * distance;

	eye.x += (*matrix)[0].x * distance;
	eye.y += (*matrix)[1].x * distance;
	eye.z += (*matrix)[2].x * distance;

	bMatrixUpdate = true;
}

// Translates along the Camera's y-axis
void BaseCamera::MoveUp(float distance)
{
	target.x += (*matrix)[0].x * distance;
	target.y += (*matrix)[1].x * distance;
	target.z += (*matrix)[2].x * distance;

	eye.x += (*matrix)[0].x * distance;
	eye.y += (*matrix)[1].x * distance;
	eye.z += (*matrix)[2].x * distance;

	bMatrixUpdate = true;
}

// Translates along the World's x-axis.
void BaseCamera::TranslateX(float distance)
{
	target.x += distance;
	eye.x += distance;

	bMatrixUpdate = true;
}

// Translates along the World's y-Axis
void BaseCamera::TranslateY(float distance)
{
	target.y += distance;
	eye.y += distance;

	bMatrixUpdate = true;
}

// Translates along the World's z-axis
void BaseCamera::TranslateZ(float distance)
{
	target.z += distance;
	eye.z += distance;

	bMatrixUpdate = true;
}

glm::mat4 *BaseCamera::GetMatrix() { return matrix; }

glm::mat4 *BaseCamera::GetProjectionMatrix() { return projection; }

glm::vec3 *BaseCamera::GetPosition() { return &eye; }