#pragma once

#include "Camera.h"

class FreelookCamera : public Camera
{
protected:
	void InitMatrix();

	void ConstructMatrix();

	void RotateX();
	void RotateY();
	void RotateZ();

public:
	FreelookCamera()
	{}
	~FreelookCamera()
	{}
};

