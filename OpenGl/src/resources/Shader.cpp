#include "Shader.h"


namespace MGLE {
	Shader::Shader(tString sVPath, tString sFPath)
	{
		Log("Loading Shader Program...\n");
		Log("--------------------------------------------------------\n");
		program  = glCreateProgram();
		GLuint v = AddShader(LoadShader(sVPath), GL_VERTEX_SHADER);
		GLuint f = AddShader(LoadShader(sFPath), GL_FRAGMENT_SHADER);
		CompileProgram(v,f);
		AddUniform("MVP");
	}
	Shader::~Shader()
	{
		glDeleteProgram(program);
	}
	GLuint Shader::GetProgramID() {
		return program;
	}
	void Shader::Bind() {
		glUseProgram(program);
	}
	tString Shader::LoadShader(tString asFilePath) {
		tString shaderSource;
		asFilePath = GetAbsolutePath() + asFilePath;
		Log("Loading Shader: %s\n", asFilePath.c_str());
		std::ifstream shaderReader(asFilePath, std::ios::in);
		if (shaderReader.is_open()) {
			tString Line = "";
			while (getline(shaderReader, Line))
				shaderSource += "\n" + Line;
			//TODO: pass in lines to uniform func
		}
		else {
			FatalError("Couldn't open shader: %s. Is the directory correct?\n", asFilePath.c_str());
		}
		shaderReader.close();
		return shaderSource;
	}
	GLuint Shader::AddShader(tString sSource, int type)
	{
		GLuint shader = glCreateShader(type);

		if (shader == 0)
			FatalError("Shader creation failed: Could not find valid memory location when adding shader");

		const char* cSource = sSource.c_str();
		glShaderSource(shader, 1, &cSource, NULL);
		glCompileShader(shader);
		GLint Result = GL_FALSE;
		GLint InfoLogLength;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			GLchar* strInfoLog = new GLchar[InfoLogLength + 1];
			glGetShaderInfoLog(shader, InfoLogLength, NULL, strInfoLog);
			FatalError("Shader compile error:\n%s\n %s.\n", sSource.c_str(), strInfoLog);
		}
		glAttachShader(program, shader);
		return shader;
	}
	void Shader::CompileProgram(GLuint v, GLuint f)
	{
		GLint Result = GL_FALSE;
		GLint InfoLogLength;
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &Result);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			GLchar* strInfoLog = new GLchar[InfoLogLength + 1];
			glGetProgramInfoLog(program, InfoLogLength, NULL, strInfoLog);
			FatalError("Shader Link Error: %s. \n", strInfoLog);
		}
		glDetachShader(program, v);
		glDetachShader(program, f);

		glDeleteShader(v);
		glDeleteShader(f);

		glValidateProgram(program);
		glGetProgramiv(program, GL_VALIDATE_STATUS, &Result);
		if (Result == GL_FALSE) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			FatalError("Shader Validate Error: %s. \n", &ProgramErrorMessage[0]);
		}
	}

	void Shader::AddUniform(tString sUniform) {
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
	void Shader::SetUniform(tString uniformName, int value)
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
	void Shader::SetUniform(tString uniformName, float value)
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
	void Shader::SetUniform(tString uniformName, Vector3 value)
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
	void Shader::SetUniform(tString uniformName, Mat4x4 value)
	{
		try {
			glUniformMatrix4fv(mUniforms.at(uniformName), 1, GL_TRUE, &value.m[0]);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}
}
