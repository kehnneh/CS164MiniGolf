#pragma once

#include <glm\glm.hpp>
#include <vector>

class BaseCamera
{
private:
	std::vector<void(BaseCamera::*)()> _pipeline;

	bool bProjectionUpdate, bMatrixUpdate;

	void Maketrix(bool& update, void(BaseCamera::*)(void));

	void ProjectionMatrix();

protected:
	// X.x Y.x Z.x  0
	// X.y Y.y Z.y  0
	// X.z Y.z Z.z  0
	//  0   0   0   1
	glm::mat4 *matrix;
	glm::mat4 *projection;

	// *matrix = glm::lookAt(eye, target, up)
	glm::vec3 eye, target, up;

	float pitch, yaw;
	const float roll;

	// This gets implemented in inherited classes
	virtual void Matrix();
	virtual void InitMatrix();

	void ThirdPerson();
	void TranslateToTarget();

	void RotateX();
	void RotateY();
	void RotateZ();

public:
	BaseCamera()
	: pitch(-45.f),
	  yaw(0.f),
	  roll(0.f),
	  bProjectionUpdate(true),
	  bMatrixUpdate(true),
	  eye(0.f, 0.f, 0.f),
	  target(0.f, 0.f, 0.f),
	  up(0.f, 1.f, 0.f)
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

	void MoveForward(float distance);
	void MoveLeft(float distance);
	void MoveUp(float distance);

	void TranslateX(float distance);
	void TranslateY(float distance);
	void TranslateZ(float distance);

	void Tick();

	glm::mat4 *GetMatrix();
	glm::mat4 *GetProjectionMatrix();
	glm::vec3 *GetPosition();
};

