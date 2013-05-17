#include "BaseCamera.h"
#include "CommonUtils.h"

#include <glm\core\func_trigonometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

static float fovy = 45.f,
			 aspect = 640.f / 480.f,
			 znear = 0.1f,
			 zfar = 10000.f;

static const glm::vec3 XAXIS(1.f, 0.f, 0.f);
static const glm::vec3 YAXIS(0.f, 1.f, 0.f);
static const glm::vec3 ZAXIS(0.f, 0.f, 1.f);

static const float pitch_limit = 90.f;
static const float scale = 6.f;

// Performs memory allocation!
void BaseCamera::Init()
{
	matrix = new glm::mat4;
	projection = new glm::mat4;
}

void BaseCamera::DeInit()
{
	SAFE_DELETE(matrix);
	SAFE_DELETE(projection);
}

void BaseCamera::ProjectionMatrix()
{
	*projection = glm::perspective(fovy, aspect, znear, zfar);
}

void BaseCamera::Matrix()
{
	// Initialize the matrix at the origin
	*matrix = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), up);
	// Perform rotations at the origin
	*matrix = glm::rotate(*matrix, pitch, XAXIS);
	*matrix = glm::rotate(*matrix, yaw, YAXIS);

	// Translates the camera such that it is positioned at the fixed point
	// Here, target is the fixed point to rotate about
	*matrix = glm::translate(*matrix, target);

	// Grab the Camera's z-axis vector and move negatively along it
	glm::vec3 z_late((*matrix)[0].z, (*matrix)[1].z, (*matrix)[2].z);
	*matrix = glm::translate(*matrix, z_late * -5.f);
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
void BaseCamera::RotateX()
{
	*matrix = glm::rotate(*matrix, pitch, XAXIS);
}

// Rotates the Camera around the Y-Axis by the Camera's Yaw value
void BaseCamera::RotateY()
{
	*matrix = glm::rotate(*matrix, yaw, YAXIS);
	//*matrix = glm::rotate(yaw, YAXIS) * *matrix; // free look!
}

// Translates along the Camera's X-Axis
void BaseCamera::TranslateX(float distance)
{
	glm::vec3 x_late((*matrix)[0].x, (*matrix)[1].x, (*matrix)[2].x);

	target -= x_late * distance;
	eye -= x_late * distance;

	bMatrixUpdate = true;
}

// Translates along the Camera's Y-Axis
void BaseCamera::TranslateY(float distance)
{
	bMatrixUpdate = true;
}

// Translates along the Camera's Z-axis
void BaseCamera::TranslateZ(float distance)
{
	bMatrixUpdate = true;
}

// Translate differs depending on the kind of camera. For instance,
// Arcball cameras translate along their negative z-axis, while
// Freelook cameras
void BaseCamera::Translate()
{
	// Translate in the direction (0, 0, -1) relative to the Camera's ZAXIS
	glm::vec3 z_late((*matrix)[0].z, (*matrix)[1].z, (*matrix)[2].z);
	glm::vec3 y_late((*matrix)[0].y, (*matrix)[1].y, (*matrix)[2].y);
	glm::vec3 x_late((*matrix)[0].x, (*matrix)[1].x, (*matrix)[2].x);

	//eye = (x_late * translation.x) + (y_late * translation.y) + (z_late * translation.z);

	z_late.y = 0.f;
	//target = (x_late * translation.x) + (y_late * translation.y) + (z_late);

	*matrix = glm::translate(*matrix, -eye);
	//*matrix = glm::translate(-eye) * *matrix;
}

glm::mat4 *BaseCamera::GetMatrix()
{
	return matrix;
}

glm::mat4 *BaseCamera::GetProjectionMatrix()
{
	return projection;
}

glm::vec3 *BaseCamera::GetPosition()
{
	return &eye;
}