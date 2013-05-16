#pragma once

#include <glm\glm.hpp>

class BaseCamera
{
private:
	bool bProjectionUpdate, bMatrixUpdate;

	void Maketrix(bool& update, void(BaseCamera::*)(void));

	void ProjectionMatrix();

protected:
	glm::mat4 *matrix, *projection;

	// Eye is where the eye is located.
	// Translation is the amount the camera is translated in the xyz directions
	// relative to the camera's xyz-axes
	glm::vec3 eye, translation;

	float pitch, yaw;

	// This gets implemented in inherited classes
	virtual void Matrix();

	void RotateX();
	void RotateY();
	void Translate();

public:
	BaseCamera()
	: pitch(-45.f),
	  yaw(0.f),
	  bProjectionUpdate(true),
	  bMatrixUpdate(true),
	  translation(0.f, 0.f, 0.f),
	  eye(0.f, 0.f, 0.f)
	{}
	virtual ~BaseCamera()
	{}

	void Init();
	void DeInit();

	void SetFOV(float fov);
	void SetScreenSize(float x, float y);
	void SetFarPlane(float z);

	void IncYaw(float degrees);
	void IncPitch(float degrees);

	void TranslateX(float distance);
	void TranslateY(float distance);
	void TranslateZ(float distance);

	void Tick();

	glm::mat4 *GetMatrix();
	glm::mat4 *GetProjectionMatrix();
	glm::vec3 *GetPosition();
};

