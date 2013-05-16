#include "Kengine.h"
#include "Shader.h"
#include "UserInput.h"
#include "CommonUtils.h"
#include "Camera.h"
#include "Level.h"

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

	kengine->level->Render(kengine->camera, kengine->shader);

	glutSwapBuffers();
}

void Tick(int value)
{
	// Send new values to the shaders
	glUniform3fv(kengine->shader->eye, 1, (GLfloat*) kengine->camera->GetEyePosition());
	glUniformMatrix4fv(kengine->shader->mat_camera, 1, GL_FALSE, (GLfloat*) kengine->ac->GetMatrix());//kengine->camera->GetMatrix());
	glUniformMatrix4fv(kengine->shader->mat_projection, 1, GL_FALSE, (GLfloat*) kengine->camera->GetProjectionMatrix());

	// Handle user input
	//kengine->userInput->Tick();

	if (kengine->userInput->IsKeyPressed('q'))
	{
		kengine->ac->IncYaw(-1.f);
	}
	else if (kengine->userInput->IsKeyPressed('e'))
	{
		kengine->ac->IncYaw(1.f);
	}
	else if (kengine->userInput->IsKeyPressed('w'))
	{
		kengine->ac->IncPitch(1.f);
	}
	else if (kengine->userInput->IsKeyPressed('s'))
	{
		kengine->ac->IncPitch(-1.f);
	}

	kengine->ac->Tick();

	glutPostRedisplay();
	glutTimerFunc(20, Tick, 0);
}

Kengine::Kengine()
{
	kengine = this;
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

	camera = new Camera;
	camera->Init(glm::vec3(3.f, 4.f, 3.f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.f, .0f));

	ac = new ArcballCamera;
	ac->Init(glm::vec3(4.f, 4.f, 0.f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.f, .0f));

	userInput = new UserInput;
	userInput->BindCamera(camera);

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

Kengine::~Kengine()
{
	SAFE_DELETE(userInput);
	SAFE_DELETE(shader);
}
