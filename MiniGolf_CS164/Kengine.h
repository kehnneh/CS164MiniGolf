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

	Kengine();
	~Kengine();

	bool Init(int argc, char** argv);

	void Run();
};