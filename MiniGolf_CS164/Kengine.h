#pragma once

class UserInput;
class Shader;
class Camera;
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
	Camera *camera;
	Level *level;

	Kengine();
	~Kengine();

	bool Init(int argc, char** argv);

	void Run();
};

static Kengine *kengine = 0;