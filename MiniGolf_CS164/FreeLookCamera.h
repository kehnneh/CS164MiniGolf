#pragma once
#include "basecamera.h"
class FreeLookCamera : public BaseCamera
{
private:
	float pitch, yaw;
	glm::vec3 eye;

protected:
	void ConstructMatrix();

public:
	FreeLookCamera();
	~FreeLookCamera();

	void RotateX(float amt);
	void RotateY(float amt);
};

