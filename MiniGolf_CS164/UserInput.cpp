#include <gl\freeglut.h>

#include "UserInput.h"
#include "Camera.h"

void UserInput::Init()
{
	memset(&m_keys, 0, 256 * sizeof(bool));
}

void UserInput::DeInit()
{
	camera = 0;
}

void UserInput::PressKey(unsigned char key)
{
	m_keys[key] = true;
}

void UserInput::ReleaseKey(unsigned char key)
{
	m_keys[key] = false;
}

bool UserInput::IsKeyPressed(unsigned char key)
{
	return m_keys[key];
}

void UserInput::BindCamera(Camera* c)
{
	camera = c;
}

void UserInput::Tick()
{
	if (IsKeyPressed(27))
	{
		glutLeaveMainLoop();
	}
	else if (IsKeyPressed('q'))
	{
		camera->IncYaw(-1.f);
	}
	else if (IsKeyPressed('e'))
	{
		camera->IncYaw(1.f);
	}
	else if (IsKeyPressed('z'))
	{
		camera->IncPitch(-1.f);
	}
	else if (IsKeyPressed('x'))
	{
		camera->IncPitch(1.f);
	}
	else if (IsKeyPressed('a'))
	{
		camera->MoveLeft(-.25f);
	}
	else if (IsKeyPressed('d'))
	{
		camera->MoveLeft(.25f);
	}
	// Until the Camera moves along the World's X/Z plane, MoveForward is not going to work as desired
	
	else if (IsKeyPressed('w'))
	{
		camera->MoveForward(.25f);
	}
	else if (IsKeyPressed('s'))
	{
		camera->MoveForward(-.25f);
	}
	
}