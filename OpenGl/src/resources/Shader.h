#pragma once
#include "stdafx.h"
#include "MGLE.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <map>

namespace MGLE {
	typedef std::string tString;
	class Shader
	{
		std::map<tString, GLint> mUniforms;
		GLuint program;
		tString LoadShader(tString asFilePath);
		GLuint AddShader(tString sSource, int type);
		void CompileProgram(GLuint v, GLuint f);
		void AddAllUniforms();
		GLuint LoadFromFile(tString sVPath, tString sFPath);
	public:
		Shader(std::string sVPath, std::string sFPath);
		~Shader();
		GLuint GetProgramID();
		void Bind();
		void SetUniform(tString uniformName, int value);
		void SetUniform(tString uniformName, float value);
		void SetUniform(tString uniformName, Vector3 value);
		void SetUniform(tString uniformName, Mat4x4 value);
		void SetUniform(tString uniformName, glm::mat4 value);
		void AddUniform(tString uniform);
	};
}

