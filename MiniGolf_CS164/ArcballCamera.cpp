#include "ArcballCamera.h"

void ArcballCamera::SetupPipeline()
{
	_pipeline.push_back(&Camera::InitMatrix);
	_pipeline.push_back(&Camera::RotateX);
	_pipeline.push_back(&Camera::RotateY);
	// No rolling around here
	// _pipeline.push_back(&Camera::RotateZ);
	_pipeline.push_back(&Camera::TranslateToTarget);
	_pipeline.push_back(&Camera::ThirdPerson);
}

void ArcballCamera::RotateX()
{

}