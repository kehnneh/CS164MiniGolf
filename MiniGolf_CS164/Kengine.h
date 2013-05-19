#pragma once

#include "Camera.h"

class UserInput;
class Shader;
class Level;
class Projection;

class Kengine
{
private:
	int windowId;

	void InitGlut(int argc, char** argv);
	void InitCallbacks();

public:
	int activeCamera;

	Shader *shader;

	UserInput *userInput;
	Projection *_projection;
	Camera *c[2];
	Level *level;

	Kengine()
		: shader(0),
		  userInput(0),
		  c(),
		  level(0),
		  activeCamera(0)
	{}
	~Kengine()
	{}

	bool Init(int argc, char** argv);
	void DeInit();

	void Run();
};