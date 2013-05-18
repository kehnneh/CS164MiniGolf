#include "FreelookCamera.h"

#include <glm\gtx\transform.hpp>

void FreelookCamera::InitMatrix()
{
	*_mat = glm::lookAt(_origin, _direction, _up);
	//*_mat = glm::translate(_eye
}

void FreelookCamera::RotateX()
{
	*_mat = glm::rotate(_pitch, _xaxis) * *_mat;
}

void FreelookCamera::RotateY()
{
	*_mat = glm::rotate(_yaw, _yaxis) * *_mat;
}

void FreelookCamera::RotateZ()
{
	*_mat = glm::rotate(_roll, _zaxis) * *_mat;
}

void FreelookCamera::ConstructMatrix()
{
	InitMatrix();
	TranslateToEye();
	//TranslateToTarget();
	RotateX();
	RotateY();
	
	ThirdPerson();
}