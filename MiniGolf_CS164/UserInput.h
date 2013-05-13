#pragma once

class UserInput
{
private:
	bool m_keys[256];

public:
	UserInput();
	~UserInput();

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);
	bool IsKeyPressed(unsigned char key);
};

