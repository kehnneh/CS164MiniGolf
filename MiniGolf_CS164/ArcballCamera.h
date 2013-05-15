#pragma once
#include "basecamera.h"

class ArcballCamera : public BaseCamera
{
private:
	glm::vec3 eye, target, up;

protected:
	void ConstructMatrix();

public:
	ArcballCamera();
	~ArcballCamera();

	void Init(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

	void Rotate(float amt, glm::vec3 axis);

	void SetPosition(glm::vec3 eye);
	void SetTarget(glm::vec3 target);
	void SetUp(glm::vec3 up);
};

