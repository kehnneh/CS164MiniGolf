#include <gl\freeglut.h>

#include "UserInput.h"
#include "BaseCamera.h"

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

void UserInput::BindCamera(BaseCamera* c)
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
	else if (IsKeyPressed('w'))
	{
		camera->IncPitch(1.f);
	}
	else if (IsKeyPressed('s'))
	{
		camera->IncPitch(-1.f);
	}
	else if (IsKeyPressed('a'))
	{
		camera->MoveLeft(.25f);
	}
	else if (IsKeyPressed('d'))
	{
		camera->MoveLeft(-.25f);
	}
	else if (IsKeyPressed('z'))
	{
		camera->MoveForward(.25f);
	}
	else if (IsKeyPressed('x'))
	{
		camera->MoveForward(-.25f);
	}
}