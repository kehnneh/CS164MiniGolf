#include "FreeLookCamera.h"

#include <glm\gtx\transform.hpp>

static const float pitch_bound = 90.f;

using namespace glm;

FreeLookCamera::FreeLookCamera()
{
	pitch = yaw = 0.f;
}

FreeLookCamera::~FreeLookCamera()
{
}

void FreeLookCamera::ConstructMatrix()
{
	*matrix = rotate(pitch, vec3(1.f, 0.f, 0.f)) * rotate(yaw, vec3(.0f, 1.f, .0f)) * translate(eye);
}

void FreeLookCamera::RotateX(float amt)
{
	float alteredPitch = pitch + amt;

	if (alteredPitch <= pitch_bound && alteredPitch >= -pitch_bound)
	{
		pitch = alteredPitch;
	}
}

void FreeLookCamera::RotateY(float amt)
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