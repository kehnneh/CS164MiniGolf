#pragma once

class Camera;

class UserInput
{
private:
	// External links to variables controlled via UserInput::Tick()
	Camera* camera;

private:
	// Internal data
	bool m_keys[256];

public:
	UserInput();
	~UserInput();

	inline bool IsKeyPressed(unsigned char key);

	void BindCamera(Camera* c);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

	void Tick();
};

