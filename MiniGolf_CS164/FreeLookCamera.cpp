#include "FreeLookCamera.h"

#include <glm\gtx\transform.hpp>

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
	*matrix = rotate(pitch, vec3(1.f, 0.f, 0.f)) * rotate(yaw, vec3(.0f, 1.f, .0f));
}