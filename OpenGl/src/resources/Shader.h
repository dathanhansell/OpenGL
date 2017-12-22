#pragma once
#include "stdafx.h"
#include "MGLE.h"
#include <map>
namespace MGLE {
	class Shader
	{
		std::map<std::string, GLint> mUniforms;
		GLuint program;
		GLuint LoadFromFile(std::string sVPath, std::string sFPath);
	public:
		Shader(std::string sVPath, std::string sFPath);
		~Shader();
		GLuint GetProgramID();
		void SetUniform(std::string uniformName, int value);
		void SetUniform(std::string uniformName, float value);
		void SetUniform(std::string uniformName, Vector3 value);
		void SetUniform(std::string uniformName, Mat4x4 value);
		void AddUniform(std::string uniform);
	};
}

