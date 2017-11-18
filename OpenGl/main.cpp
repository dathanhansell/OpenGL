#include "stdafx.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glut.h>
#include <stdio.h>
#include <string>


using namespace std;

bool b_exit = false;
bool fullsscreen = false;
bool down = true;
bool jump = true;

Vector2 input;

Vector3 velocity{ 0,0,0 };
Vector3 rot{ 0,0,0 };

AudioClip steps[4] = { "stone1.ogg" , "stone2.ogg" ,"stone3.ogg" ,"stone4.ogg" };
int cIndex = 0;
const float gravity = -3;
bool grounded;
float stepTimer;
AudioSource source;

GLuint shader;
Model plane;
void ResetWindow() {
	glutReshapeWindow(Display::width, Display::height);
	glutPositionWindow(0, 0);
}
void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(90.0f, (GLfloat)w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}
void DoTheInput() {
	input.print("input: ");
	//input = Vector2::zero;
	if (Input::Keys['w']) {
		input.y += 1;
	}
	else if (Input::Keys['s']) {
		input.y -= 1;
	}
	else if(input.y > 0){
		input.y -= .0001f;
	}
	else {
		input.y = 0;
	}
	if (Input::Keys['a']) {
		input.x += 1;
	}
	else if (Input::Keys['d']) {
		input.x -= 1;
	}
	else if (input.x > 0) {
		input.x -= .0001f;
	}
	else {
		input.x = 0;
	}
	if (Input::Keys[' '] ) {
		if (jump && grounded) {
			velocity.y += 1;
			Input::cam.position.y += .1f;
		}
		jump = false;
	}
	else
	{
		jump =  true;
	}

	input *= Time::deltaTime * 3.4;
	if (Input::Keys['t']) {
		if (down) {
			Input::cam.ToggleThirdperson();
		}
		down = false;
	}
	else
	{
		down = true;
	}

	Vector3 mover = (Vector3(Input::cam.forward.x, 0, Input::cam.forward.z).normalized() *= input.y) + (Input::cam.right *= input.x);
	Input::cam.position += mover;

	if (Input::Keys['f']) {
		if (fullsscreen) {
			cout << "Fullscreen = False" << endl;
			ResetWindow();
			SDL_Delay(200);
			fullsscreen = false;
		}
		else
		{
			cout << "Fullscreen = True" << endl;
			glutFullScreen();
			SDL_Delay(200);
			fullsscreen = true;
		}
	}
}
void Render()
{

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Input::cam.Render();

	rot = Vector3(Input::cam.rotation.x, Input::cam.rotation.y,0);
	//glUseProgram(shader);
	
	glEnable(GL_DEPTH_TEST);
	Debug::DrawAxes({ 0,0,-3 },rot);
	Debug::DrawAxes({ 0,0,3 }, rot);
	Debug::DrawAxes({ 3,0,0 }, rot);
	Debug::DrawAxes({ -3,0,0 }, rot);
	Debug::DrawAxes({ 0,3,0 }, rot);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glColor3f(.5f,.5f,.5f);
	glEnable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, 0, plane.vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, plane.vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisableVertexAttribArray(0);
	//Debug::DrawAxes({ 0,0,0 });
	
	glutSwapBuffers();
}
void Update()
{
	Time::setDeltaTime();

	DoTheInput();
	if (input.magnitude() > 0 && stepTimer < .5) {
		stepTimer += Time::deltaTime;
	}
	if(stepTimer >= .5) {
		source.Play(steps[cIndex],48);
		cIndex++;
		if (cIndex >= sizeof(steps) / sizeof(*steps)) cIndex = 0;
		stepTimer = 0;
	}
	SDL_Delay(16.667);
	Render();
}
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	const char *vpath = new char[strlen((const char*)SDL_GetBasePath()) + strlen(vertex_file_path) + 1];
	strcpy((char*)vpath, SDL_GetBasePath());
	strcat((char*)vpath, vertex_file_path);
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vpath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vpath);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	const char *fpath = new char[strlen((const char*)SDL_GetBasePath()) + strlen(fragment_file_path) + 1];
	strcpy((char*)fpath, SDL_GetBasePath());
	strcat((char*)fpath, fragment_file_path);
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fpath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vpath);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fpath);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}


	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	delete fpath;
	delete vpath;
	return ProgramID;
}
void InitGLStates()
{
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);
	//glActiveTexture(GL_TEXTURE0);
}
bool InitializeGL()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Display::width, Display::height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - Display::width) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - Display::height) / 2);
	glutCreateWindow("OpenGl");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (GLfloat)Display::width / Display::height, 0.1, .2);
	glMatrixMode(GL_MODELVIEW);
	return true;
}
bool InitializeGLEW() {
	
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Couldn't initialize Glew", NULL);
		exit(-3);
	}
	return true;
}
bool Initialize()
{
	cout << "Initializing SDL..." << endl;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Initialize Error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Couldn't initialize SDL Audio", NULL);
		exit(-2);
		return false;
	}
	Time::SetStartTicks();
	AudioManager::SetupAudio();
	cout << "Loading Chunks..." << endl;
	for (int x = 0; x < sizeof(steps) / sizeof(*steps); x++) {
		cout << "Loading AudioClip: " << steps[x].file << endl;
		steps[x].Load();
	}

	InitGLStates();
	cout << "Initializing OpenGL..." << endl;
	if (!InitializeGL())
	{
		printf("Unable to initialize OpenGL!\n");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Unable to initialize OpenGL!", NULL);
		exit(-4);
		return false;
	}
	cout << "Initializing GLEW..." << endl;
	if (!InitializeGLEW())
	{
		printf("Unable to initialize GLEW!\n");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Unable to initialize GLEW!", NULL);
		exit(-5);
		return false;
	}
	shader = LoadShaders("vertex.glsl","frag.glsl");
	plane = ObjLoader::loadOBJ("room.obj");
	Input::SetupInput();
	glutReshapeFunc(Reshape);
	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glutMainLoop();
	return true;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	if (!Initialize())
	{
		printf("Initialize Error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error Error", "Couldn't initialize... for some reason", NULL);
		exit(-1);
	}
	SDL_Quit();
	return 0;
}