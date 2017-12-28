#include "Shader.h"


namespace MGLE {
	static tString nullVert = "#version 330 core\nlayout(location = 0) in vec3 vertexPosition;uniform mat4 MVP;void main() {gl_Position = MVP * vec4(vertexPosition,1);}";
	static tString nullFrag = "#version 330 core\nout vec3 color;void main(){color = vec3(1, 0, 1);}";
	static Shader null;
	Shader::Shader()
	{

	}
	void InitNull() {
		Log("Loading Shader Program null...\n");
		Log("--------------------------------------------------------\n");
		null.CreateFromSource("null", nullVert, nullFrag);
		null.AddUniform("MVP");
		Log("--------------------------------------------------------\n");
	}
	void Shader::SetNull() {
		Log("shader %s setting to NULL\n",name.c_str());
		if ("" == null.name) FatalError("Tried to set shader to null but null shader wasn't initalized.");
		*this = null;
	}
	void Shader::Init() {
		InitNull();
	}
	Shader::Shader(tString Name, tString sVPath, tString sFPath)
	{
		Log("Loading Shader Program %s...\n", Name.c_str());
		Log("--------------------------------------------------------\n");
		CreateFromFile(Name ,sVPath, sFPath);
		
	}
	Shader::Shader(tString Name, tString Vertex, tString Fragment, int createType)
	{
		Log("Loading Shader Program %s...\n",Name.c_str());
		Log("--------------------------------------------------------\n");
		switch (createType)
		{
		case 0:
			CreateFromFile(Name, Vertex, Fragment);
			break;
		case 1:
			
			CreateFromSource(Name, Vertex, Fragment);
			break;
		default:
			break;
		}
		
	}
	Shader::~Shader()
	{
		glDeleteProgram(program);
	}
	GLuint Shader::GetProgramID() {
		return program;
	}
	void Shader::Bind() {
		if ("" != name){
			//Log("Bind %s\n", name.c_str());
		glUseProgram(program);
	}
		else if (!nullWarning) {
			Warning("Tried to bind shader, \"%s\" but is null.\n",name.c_str());
			SetNull();
			nullWarning = true;
			Bind();
		}
		else {
			Error("Couldn't set null shader to null!");
		}
	}
	void Shader::CreateFromSource(tString Name, tString sVSource, tString sFSource) {
		name = Name;
		program = glCreateProgram();
		GLuint v, f;
		if (AddShader(sVSource, GL_VERTEX_SHADER, v) && AddShader(sFSource, GL_FRAGMENT_SHADER, f)) {
			if (CompileProgram(v, f));
			else {
				Error("Failure to compile shader %s\n", name.c_str());
				return;
			}
		}
		else {
			Error("Failure to add shader %s\n",name.c_str());
			return;
		}
		
		nullWarning = false;
		
	}
	void Shader::CreateFromFile(tString Name, tString sVPath, tString sFPath) {
		tString v, f;
		if(LoadShader(sVPath,v) && LoadShader(sFPath,f))CreateFromSource(Name,v, f);
		else {
			Error("Failure to load shader %s\n", Name.c_str());
			return;
		}
	}
	bool Shader::LoadShader(tString asFilePath, tString& out) {
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
			Error("Couldn't open shader: %s. Is the directory correct? Setting null.\n", asFilePath.c_str());
			SetNull();
			return false;
		}
		shaderReader.close();
		out = shaderSource;
		return true;
	}
	bool Shader::AddShader(tString sSource, int type, GLuint& out)
	{
		GLuint shader = glCreateShader(type);

		if (shader == 0) {
			Error("Shader creation failed: Could not find valid memory location when adding shader, setting null");
			SetNull();
		}

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
			Error("Shader compile error, setting null:\n%s\n %s.\n", sSource.c_str(), strInfoLog);
			SetNull();
			return false;
		}
		glAttachShader(program, shader);
		out = shader;
		return true;
	}
	bool Shader::CompileProgram(GLuint v, GLuint f)
	{
		GLint Result = GL_FALSE;
		GLint InfoLogLength;
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &Result);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			GLchar* strInfoLog = new GLchar[InfoLogLength + 1];
			glGetProgramInfoLog(program, InfoLogLength, NULL, strInfoLog);
			Error("Shader link error, setting null: %s\n%s. \n",name.c_str(), strInfoLog);
			SetNull();
			return false;
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
			Error("Shader Validate Error, setting null: %s\n%s. \n", name.c_str(), &ProgramErrorMessage[0]);
			SetNull();
			return false;
		}
		return true;
	}

	void Shader::AddUniform(tString sUniform) {
		Log("Adding Uniform %s\n",sUniform.c_str());
		GLint iLocation = glGetUniformLocation(program, sUniform.c_str());
		if (iLocation == 0xFFFFFFFF)
		{
			FatalError("Couldn't find uniform: %s \nCheck to see if you used it in void main()\n", sUniform.c_str(), iLocation);
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
			Log("Uniform %s added to program! Location: %i\n", sUniform.c_str(), iLocation);
		}
	}
	void Shader::SetUniform(tString uniformName, int value)
	{
		try {
			int size = mUniforms.size();
			//if (size > 0)
			glProgramUniform1i(program, mUniforms.at(uniformName), value);
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
			glProgramUniform1f(program, mUniforms.at(uniformName), value);
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
			glProgramUniform3f(program, mUniforms.at(uniformName), value.x, value.y, value.z);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}
	void Shader::SetUniform(tString uniformName, Mat4x4 value)
	{
		try {
			glProgramUniformMatrix4fv(program,mUniforms.at(uniformName), 1, GL_TRUE, &value.m[0]);
		}
		catch (const std::out_of_range& e) {
			FatalError("Failure to set uniform %s : Out of Range Exception: %s\n", uniformName.c_str(), e.what());
		}
	}
	
}
