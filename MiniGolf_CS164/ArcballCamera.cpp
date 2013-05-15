#include "ArcballCamera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;

ArcballCamera::ArcballCamera() {}

ArcballCamera::~ArcballCamera() {}

void ArcballCamera::Init(vec3 eye, vec3 target, vec3 up)
{
	// Make sure Init from BaseCamera is called! It allocates memory!
	BaseCamera::Init();

	this->eye = eye;
	this->target = target;
	this->up = up;

	ConstructMatrix();
}

void ArcballCamera::ConstructMatrix()
{
	*matrix = lookAt(eye, target, up);
}

void ArcballCamera::Rotate(float amt, vec3 axis)
{
	eye = vec3(rotate(amt, axis) * vec4(eye - target, .0f)) + target;
	ConstructMatrix();
}

void ArcballCamera::SetPosition(vec3 eye)
{
	this->eye = eye;
	ConstructMatrix();
}

void ArcballCamera::SetTarget(vec3 target)
{
	this->target = target;
	ConstructMatrix();
}

void ArcballCamera::SetUp(vec3 up)
{
	this->up = up;
	ConstructMatrix();
}
