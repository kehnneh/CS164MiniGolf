#include "UserInput.h"

UserInput::UserInput()
{
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