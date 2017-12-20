#include "Resources.h"
namespace MGLE {
	Resources::Resources() {
		objloader = new ObjLoader();
		mLowLevelSystem = new cLowLevelSystem();
		LoadShaders("shaders\\vert.glsl", "shaders\\frag.glsl");

	}
	Resources::~Resources() {
		delete objloader;
	}
	GLuint shader;
	GLuint Resources::LoadShaders(std::string vertex_file_path, std::string fragment_file_path) {
		
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Vertex Shader
		vertex_file_path = GetAbsolutePath() + vertex_file_path;
		Log("Loading Shader Program...\n");
		Log("--------------------------------------------------------\n");
		Log("Loading Vertex Shader: %s\n", vertex_file_path.c_str());
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			Error("Couldn't open Vert Shader: %s. Is the directory correct?\n", vertex_file_path.c_str());
			getchar();
			return 0;
		}

		// Fragment Shader
		
		fragment_file_path = GetAbsolutePath() + fragment_file_path;
		Log("Loading Fragment Shader: %s\n", fragment_file_path.c_str());
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else {
			Error("Couldn't open Frag Shader: %s. Is the directory correct?\n", fragment_file_path.c_str());
			getchar();
			return 0;
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;


		// Compile Vertex Shader
		Log("Compiling Vertex shader : %s\n", vertex_file_path.c_str());
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			Error("Vert Shader:%s Compile Error: %s. \n", vertex_file_path.c_str(), &VertexShaderErrorMessage[0]);
		}



		// Compile Fragment Shader
		Log("Compiling Fragment shader : %s\n", fragment_file_path.c_str());
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			Error("Frag Shader:%s Compile Error: %s. \n", fragment_file_path.c_str(), &FragmentShaderErrorMessage[0]);
		}


		// Link the program
		Log("Linking program\n");
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
			Error("Shader Link Error: %s. \n", &ProgramErrorMessage[0]);
		}


		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
		Log("Done!\n");
		Log("--------------------------------------------------------\n");
		return ProgramID;
	}
}