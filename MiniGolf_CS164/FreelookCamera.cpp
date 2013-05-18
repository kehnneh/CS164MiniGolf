#include "FreelookCamera.h"

#include <glm\gtx\transform.hpp>

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

}