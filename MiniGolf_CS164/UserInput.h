#pragma once

class BaseCamera;

class UserInput
{
private:
	// External links to variables controlled via UserInput::Tick()
	BaseCamera* camera;

private:
	// Internal data
	bool m_keys[256];

public:
	UserInput()
		: camera(0),
#pragma warning( suppress : 4351 )
		  m_keys()
	{}
	~UserInput()
	{}

	inline bool IsKeyPressed(unsigned char key);

	void BindCamera(BaseCamera* c);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

	void Tick();

	void Init();
	void DeInit();
};

