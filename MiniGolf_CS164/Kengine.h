#pragma once

class UserInput;
class Shader;
class Camera;
class Level;

class Kengine
{
private:
	int windowId;

	Shader *shader;

	void InitGlut(int argc, char** argv);
	void InitCallbacks();

public:
	UserInput *userInput;
	Camera *camera;
	Level *level;

	Kengine();
	~Kengine();

	bool Init(int argc, char** argv);

	void Run();
};

static Kengine *kengine;