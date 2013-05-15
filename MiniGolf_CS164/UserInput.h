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

	inline bool IsKeyPressed(unsigned char key);

public:
	UserInput();
	~UserInput();

	void BindCamera(Camera* c);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

	void Tick();
};

