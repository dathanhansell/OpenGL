#pragma once
#include "stdafx.h"
#include "MGLE.h"
#include <map>

namespace MGLE {
	typedef std::string tString;
	class Shader
	{
		void SetNull();
		tString name;
		bool  nullWarning = false;
		std::map<tString, GLint> mUniforms;
		GLuint program;
		bool LoadShader(tString asFilePath, tString& out);
		bool AddShader(tString sSource, int type, GLuint& out);
		bool CompileProgram(GLuint v, GLuint f);
		void AddAllUniforms();
		void CreateFromSource(tString Name, tString sVSource, tString sFSource);
		void CreateFromFile(tString Name, tString sVPath, tString sFPath);
	public:
		#define FROM_FILE  0
		#define FROM_SOURCE  1
		Shader();
		static void Init();
		Shader(tString Name, tString sVMisc, tString sFMisc, int createType = 0);
		~Shader();
		GLuint GetProgramID();
		void CreateProgram(tString Name, tString sVMisc, tString sFMisc, int createType = 0);
		void Bind();
		void SetUniform(tString uniformName, int value);
		void SetUniform(tString uniformName, float value);
		void SetUniform(tString uniformName, Vector3 value);
		void SetUniform(tString uniformName, Mat4x4 value);
		void AddUniform(tString uniform);
	};
}

