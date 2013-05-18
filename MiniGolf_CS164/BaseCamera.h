#pragma once

#include <glm\glm.hpp>
#include <vector>

class BaseCamera
{
private:
	std::vector<void(BaseCamera::*)()> _pipeline;

	bool _bProjectionUpdate, _bMatrixUpdate;

	void Maketrix(bool& update, void (BaseCamera::*)());

	/* Put the following block in a Projection class */
	/////////////////////////////////////////
	void ProjectionMatrix();
	/////////////////////////////////////////

protected:
	// Static constants need to be defined in the class's source file.
	// See BaseCamera.cpp for initialization.
	// These particular values will *never* change. They are relative to the World.
	static const glm::vec3 _origin, _xaxis, _yaxis, _zaxis;

	// This is the direction which the Camera faces after InitMatrix() is called
	glm::vec3 _direction;

	// The matrix field will end up looking like the following matrix.
	// X.x Y.x Z.x  0
	// X.y Y.y Z.y  0
	// X.z Y.z Z.z  0
	//  0   0   0   1
	glm::mat4 *_matrix;

	/* Put the following block in a Projection class */
	/////////////////////////////////////////
	glm::mat4 *_projection;
	/////////////////////////////////////////

	virtual void SetupPipeline();// = 0;

	// Camera position information
	glm::vec3 _eye, _target, _up;

	// Camera rotation information. Consider using Quaternions with this data! :)
	float _pitch, _yaw, _roll;

	void Matrix();
	// TopDown::InitMatrix will need to override this such that _up and _direction are different
	virtual void InitMatrix();

	void ThirdPerson();
	void TranslateToTarget();

	virtual void RotateX();
	virtual void RotateY();
	virtual void RotateZ();

public:
	BaseCamera()
		: _pitch(-45.f), _yaw(0.f), _roll(0.f),
	      _bProjectionUpdate(true), _bMatrixUpdate(true),
	      _direction(0.f, 0.f, 1.f),
	      _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f)
	{}
	virtual ~BaseCamera()
	{}

	void Init();
	void DeInit();

	/* Put the following block in a Projection class */
	/////////////////////////////////////////
	void SetFOV(float fov);
	void SetScreenSize(float x, float y);
	void SetFarPlane(float z);
	/////////////////////////////////////////

	void IncYaw(float degrees);
	void IncPitch(float degrees);
	void IncRoll(float degrees);

	virtual void MoveForward(float distance);
	virtual void MoveLeft(float distance);
	virtual void MoveUp(float distance);

	void TranslateX(float distance);
	void TranslateY(float distance);
	void TranslateZ(float distance);

	void Tick();

	glm::mat4 *GetMatrix();
	glm::mat4 *GetProjectionMatrix();
	glm::vec3 *GetPosition();
};

