#pragma once

#include "BaseCamera.h"

class UserInput;
class Shader;
class Level;

class Kengine
{
private:
	int windowId;

	void InitGlut(int argc, char** argv);
	void InitCallbacks();

public:
	Shader *shader;

	UserInput *userInput;
	BaseCamera *c;
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