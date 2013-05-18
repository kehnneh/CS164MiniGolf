#pragma once

#include "Camera.h"

class ArcballCamera : public Camera
{
protected:
	void SetupPipeline();

	void RotateX();
	void RotateY();
	void RotateZ();

public:
	ArcballCamera()
	{}
	~ArcballCamera()
	{}

	void MoveForward(float distance);
};

