#pragma once

#include <glm\glm.hpp>

class BaseCamera
{
protected:
	glm::mat4 *matrix, *projection;

	glm::vec3 eye;

	float pitch, yaw;

	void CreateProjectionMatrix();

	virtual void ConstructMatrix() = 0;

public:
	BaseCamera();
	virtual ~BaseCamera();

	void Init();

	void SetFOV(float fov);
	void SetScreenSize(float x, float y);
	void SetFarPlane(float z);

	void RotateX();
	void RotateY();

	glm::mat4 *GetMatrix();
	glm::mat4 *GetProjectionMatrix();
};

