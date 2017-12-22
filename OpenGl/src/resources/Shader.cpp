#include "Shader.h"


namespace MGLE {
	Shader::Shader(std::string sVPath, std::string sFPath)
	{
		LoadFromFile(sVPath, sFPath);
	}


	Shader::~Shader()
	{
		glDeleteProgram(program);
	}

	void Shader::AddUniform(std::string sUniform) {
		GLint iLocation = glGetUniformLocation(program, sUniform.c_str());
		if (iLocation == 0xFFFFFFFF)
		{
			FatalError("Couldn't find uniform: %s Location = %i\n", sUniform.c_str(), iLocation);
		}

		GLint iUniforms;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &iUniforms);
		int size = (mUniforms.size() + 1);
		if (iUniforms < size) {
			Log("Program has %i != %i uniforms!\n", iUniforms, size);
			GLint InfoLogLength = 256;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
			Log("InfoLogLength: %i\n", InfoLogLength);
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			FatalError("Program uniforms < %i: %s. \n", size, &ProgramErrorMessage[0]);
		}
		else {
			mUniforms[sUniform] = iLocation;
			Log("Uniform %s added to program!\n", sUniform.c_str());
		}
	}
	GLuint Shader::GetProgramID() {
		return program;
	}
	void Shader::SetUniform(std::string uniformName, int value)
	{
		try {
			int size = mUniforms.size();
			//if (size > 0)
			glUniform1i(mUniforms.at(uniformName), value);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}

	void Shader::SetUniform(std::string uniformName, float value)
	{
		try {
			int size = mUniforms.size();
			//if (size > 0)
			glUniform1f(mUniforms.at(uniformName), value);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}

	void Shader::SetUniform(std::string uniformName, Vector3 value)
	{
		try {
			int size = mUniforms.size();
			//if (size > 0)
			glUniform3f(mUniforms.at(uniformName), value.x, value.y, value.z);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}

	void Shader::SetUniform(std::string uniformName, Mat4x4 value)
	{
		try {
			int size = mUniforms.size();
			//if (size > 0)
				glUniformMatrix4fv(mUniforms.at(uniformName), 1, GL_FALSE, value.m);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n",uniformName.c_str(),e.what());
		}
	}
	GLuint Shader::LoadFromFile(std::string sVPath, std::string sFPath) {

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Vertex Shader
		sVPath = GetAbsolutePath() + sVPath;
		Log("Loading Shader Program...\n");
		Log("--------------------------------------------------------\n");
		Log("Loading Vertex Shader: %s\n", sVPath.c_str());
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(sVPath, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			FatalError("Couldn't open Vert Shader: %s. Is the directory correct?\n", sVPath.c_str());
			return 0;
		}

		// Fragment Shader

		sFPath = GetAbsolutePath() + sFPath;
		Log("Loading Fragment Shader: %s\n", sFPath.c_str());
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(sFPath, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else {
			FatalError("Couldn't open Frag Shader: %s. Is the directory correct?\n", sFPath.c_str());
			return 0;
		}


		GLint Result = GL_FALSE;
		GLint InfoLogLength;


		// Compile Vertex Shader
		Log("Compiling Vertex shader : %s\n", sVPath.c_str());
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			FatalError("Vert Shader:%s Compile Error: %s. \n", sVPath.c_str(), &VertexShaderErrorMessage[0]);
		}



		// Compile Fragment Shader
		Log("Compiling Fragment shader : %s\n", sFPath.c_str());
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			FatalError("Frag Shader:%s Compile Error: %s. \n", sFPath.c_str(), &FragmentShaderErrorMessage[0]);
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
			FatalError("Shader Link Error: %s. \n", &ProgramErrorMessage[0]);
		}

		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		glValidateProgram(ProgramID);
		glGetProgramiv(ProgramID, GL_VALIDATE_STATUS, &Result);
		if (Result == GL_FALSE) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			FatalError("Shader Validate Error: %s. \n", &ProgramErrorMessage[0]);
		}
		Log("Done!\n");
		Log("--------------------------------------------------------\n");
		//delete VertexSourcePointer;
		//delete FragmentSourcePointer;
		return ProgramID;
	}
}
