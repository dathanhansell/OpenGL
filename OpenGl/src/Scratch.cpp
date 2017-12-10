//SDL_Delay(16.667);
//Time::setDeltaTime();

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
GLuint shader;
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