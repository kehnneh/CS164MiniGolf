#pragma once
#include "basecamera.h"
class FreeLookCamera : public BaseCamera
{
private:
	float pitch, yaw;

protected:
	void ConstructMatrix();

public:
	FreeLookCamera();
	~FreeLookCamera();
};

