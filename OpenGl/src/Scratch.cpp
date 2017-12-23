/*
////Matrix Junk////
#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <glm.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include"gtx/string_cast.hpp"
using namespace std;
namespace MGLE {
Game::Game()
{
Init();

}
Mat4x4 m, v, p, MVP;
glm::mat4 mProjection, mModel, mView,mvp;

Shader* shad;
cModel mod;
Game::~Game()
{
Log("Exiting System Module\n");
Log("--------------------------------------------------------\n");
Log("Done with Graphics\n");
delete graphics;
Log("Done with Input\n");
delete input;
Log("Done with Resources\n");
delete resources;
delete shad;
Log("--------------------------------------------------------\n\n");
}
float x = 0;
float z = 0;
void Game::Init() {

graphics = new Graphics();
input = new Input();
resources = new Resources();

p = p.Perspective(90.0f, 1.0f, 0.1f, 100.0f);
mProjection = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);


m = m.Identity();
mModel = glm::mat4(1.0f);


shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
mod = resources->objloader->LoadOBJ("test.obj");
}
float c;
void Game::Update() {
glClearColor(.2f, .2f, .2f, 1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
c += .0016;
glPushMatrix();

v = v.View({(float)sin(c*(2 * M_PI))*3, 1, (float)cos(c*(2 * M_PI))*3 },{ 0, 0, 0 },{ 0, 1, 0 });
mView = glm::lookAt(
glm::vec3((float)sin(c*(2 * M_PI)) * 3, 1, (float)cos(c*(2 * M_PI)) * 3),
glm::vec3(0, 0, 0),
glm::vec3(0, 1, 0)
);
m.Translate({x,0,z});
mModel = glm::translate(glm::mat4(1.0f),glm::vec3(x, 0, z));
mvp = mProjection * mView * mModel;
MVP = m*v*p;

if (input->GetKeyDown(input->E)) {
Log("x:%f , z:%f\n",x,z);
Log("M: %s\n", glm::to_string(mModel).c_str());
Log("\n M: %s\n", m.toString().c_str());
Log("V: %s\n", glm::to_string(mView).c_str());
Log(" V: %s\n", v.toString().c_str());
//Log("P: %s\n", glm::to_string(mProjection).c_str());
//Log(" P: %s\n", p.toString().c_str());
Log("MVP: %s\n", glm::to_string(mvp).c_str());
Log(" MVP: %s\n", MVP.toString().c_str());
}

if (input->GetKey(input->W))z += .2f;
if (input->GetKey(input->S))z -= .2f;
if (input->GetKey(input->D))x += .2f;
if (input->GetKey(input->A))x -= .2f;

shad->SetUniform("MVP", MVP);


shad->Bind();
mod.Draw();

input->Update();
}
}
/*
Debug::DrawWireSphere(Vector3::zero);
//Mercury
Planet(.2f, 5, 8, { .2f,.2f,.2f });
//Venus
Planet(.5f, 12, 7, { .7f,.7f,.2f });
//Earth
Planet(.5f, 20, 6, { .2f,.2f,.8f });
//Mars
Planet(.37f, 50, 5, { .8f,.2f,.1f });
//Jupiter
Planet(20, 200, 4, { 1,.5f,.2f });
//Saturn
Planet(15, 300, 3, { .6f,.5f,.2f });
//Neptune
Planet(8, 400, 2, { .2f,.2f,.6f });
//Uranus
Planet(7, 500, 1, { .3f,.4f,.8f });


Debug::DrawWireSphere(Vector3::zero,4.32);
//Mercury
Planet(.015f, 360, 8, { .2f,.2f,.2f });
//Venus
Planet(.038f, 672, 7, { .7f,.7f,.2f });
//Earth
Planet(.04f, 930, 6, { .2f,.2f,.8f });
//Mars
Planet(.021f, 1496, 5, { .8f,.2f,.1f });
//Jupiter
Planet(.44, 4836, 4, { 1,.5f,.2f });
//Saturn
Planet(.36, 8867, 3, { .6f,.5f,.2f });
//Neptune
Planet(.153, 17840, 2, { .2f,.2f,.6f });
//Uranus
Planet(.16, 27944, 1, { .3f,.4f,.8f });
*/
//SDL_Delay(16.667);
//Time::setDeltaTime();
/*
void Game::drawText(string text, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2i(x, y);
	for (int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	glPopMatrix();
}
*/
///////////////////////////
// Rendering Stuff
///////////////////////////
/*
glClearColor(.1f, .1f, .1f, 1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();

glEnable(GL_DEPTH_TEST);

glUseProgram(shader);

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
glDisableVertexAttribArray(0);

glutSwapBuffers();
*/
///////////////////////////
// GL States
///////////////////////////
/*
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
///////////////////////////
// Cam
///////////////////////////
Maths::Clamp(rotation.y, 89, -89);
Maths::Eulerize(rotation.x);
forward = Vector3::forward;
forward = Vector3::EulerToForwardVector({rotation.x,rotation.y,0});
up = Vector3::up;
up = Vector3::EulerToForwardVector({ rotation.x,rotation.y + 90,0 });
right = Vector3::Cross(up,forward);
gluLookAt(position.x, position.y, position.z,
forward.x + position.x, forward.y + position.y, forward.z + position.z,
0.0, 1.0, 0.0);
*/
///////////////////////////
// Reshape
///////////////////////////
/*
void Reshape(int w, int h) {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(90.0f, (GLfloat)w / h, 0.1, 100);
glMatrixMode(GL_MODELVIEW);
}
*/
///////////////////////////
// Initialize
///////////////////////////
/*
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
	shader = LoadShaders("vertex.glsl", "frag.glsl");
	plane = ObjLoader::loadOBJ("room.obj");
	Input::SetupInput();
	glutReshapeFunc(Reshape);
	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glutMainLoop();
	return true;
}
*/
/*
if (!Initialize())
{
	printf("Initialize Error: %s\n", SDL_GetError());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error Error", "Couldn't initialize... for some reason", NULL);
	exit(-1);
}
*/
///////////////////////////
// Shaders
///////////////////////////
/*

*/
///////////////////////////
// Display
///////////////////////////
/*
void ResetWindow() {
	glutReshapeWindow(Display::width, Display::height);
	glutPositionWindow(0, 0);
}
*/