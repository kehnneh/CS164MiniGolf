#pragma once

#include <glm\glm.hpp>

class BaseCamera
{
protected:
	glm::mat4 *matrix, *projection;

	glm::vec3 eye, position;

	float pitch, yaw;

	void CreateProjectionMatrix();

	void ConstructMatrix();

public:
	BaseCamera()
	: pitch(-45.f), yaw(0.f), eye(glm::vec3(0.f, 4.f, -4.f))
	{}
	virtual ~BaseCamera()
	{}

	void Init();

	void SetFOV(float fov);
	void SetScreenSize(float x, float y);
	void SetFarPlane(float z);

	void RotateX();
	void RotateY();
	void Translate();

	void IncYaw(float amt);
	void IncPitch(float amt);

	void Tick();

	glm::mat4 *GetMatrix();
	glm::mat4 *GetProjectionMatrix();
};

