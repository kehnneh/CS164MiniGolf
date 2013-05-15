#include <gl\freeglut.h>

#include "UserInput.h"
#include "Camera.h"

UserInput::UserInput()
{
	camera = 0;
	for (int i=0;i<256;i++) m_keys[i] = false;
}

UserInput::~UserInput()
{
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
		camera->ArcRotate(-1.f, glm::vec3(0.f, 1.f, 0.f));
	}
	else if (IsKeyPressed('e'))
	{
		camera->ArcRotate(1.f, glm::vec3(0.f, 1.f, 0.f));
	}
	else if (IsKeyPressed('w'))
	{
		camera->ArcRotate(1.f, glm::vec3(1.f, 0.f, 0.f));
	}
	else if (IsKeyPressed('s'))
	{
		camera->ArcRotate(-1.f, glm::vec3(1.f, 0.f, 0.f));
	}
}