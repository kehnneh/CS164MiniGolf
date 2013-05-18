#include "Kengine.h"
#include "Shader.h"
#include "UserInput.h"
#include "CommonUtils.h"
#include "Camera.h"
#include "Level.h"
#include "Projection.h"
#include "ArcballCamera.h"

static Kengine *kengine = 0;

// Registers key presses with the input manager
void keyboard(unsigned char key, int x, int y)
{
	kengine->userInput->PressKey(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	kengine->userInput->ReleaseKey(key);
}

void display()
{
	glViewport(0, 0, 640, 480);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	kengine->level->Render(kengine->c, kengine->shader);

	glutSwapBuffers();
}

void Tick(int value)
{
	kengine->_projection->Tick();

	// Send new values to the shaders
	glUniform3fv(kengine->shader->eye, 1, (GLfloat*) kengine->c->GetPosition());
	glUniformMatrix4fv(kengine->shader->mat_camera, 1, GL_FALSE, (GLfloat*) kengine->c->Matrix());//kengine->camera->GetMatrix());
	glUniformMatrix4fv(kengine->shader->mat_projection, 1, GL_FALSE, (GLfloat*) kengine->_projection->Matrix());

	// Handle user input
	kengine->userInput->Tick();

	kengine->c->Tick();

	glutPostRedisplay();
	glutTimerFunc(20, Tick, 0);
}

void Kengine::InitGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Use both!
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_AND_BACK);

	windowId = glutCreateWindow("Derp");
}

bool Kengine::Init(int argc, char** argv)
{
	if (argc < 2)
	{
		return false;
	}

	kengine = this;

	// Initialize GLUT and GLEW
	InitGlut(argc, argv);

	// TODO: Setup GLUI

	glewInit();

	// Initialize Shader
	shader = new Shader;
	if (!shader->Init("vert.glsl", "frag.glsl")) return false;
	shader->Enable();

	// Set the Renderable class to use the shader
	Renderable::BindShader(shader);

	c = new ArcballCamera;
	c->Init();

	_projection = new Projection;
	_projection->Init();
	_projection->fovy(45.f);
	_projection->znear(0.1f);
	_projection->zfar(10000.f);
	_projection->screenWidth(640);
	_projection->screenHeight(480);

	userInput = new UserInput;
	userInput->BindCamera(c);

	level = new Level;
	level->Init(argv[1]);

	InitCallbacks();

	return true;
}

void Kengine::InitCallbacks()
{
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(20, Tick, 0);
}

void Kengine::Run()
{
	glutMainLoop();
}

void Kengine::DeInit()
{
	SAFE_DELETE(userInput);
	SAFE_DELETE(shader);
}
