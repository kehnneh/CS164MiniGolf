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
	Shader *shader;

	UserInput *userInput;
	Projection *_projection;
	Camera *c;
	Level *level;

	Kengine()
		: shader(0),
		  userInput(0),
		  c(0),
		  level(0)
	{}
	~Kengine()
	{}

	bool Init(int argc, char** argv);
	void DeInit();

	void Run();
};