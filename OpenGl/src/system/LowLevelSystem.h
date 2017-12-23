#pragma once
#include "stdafx.h"
#include <windows.h>
#include "MGLE.h"


namespace MGLE {
	class cLogger
	{
		void ReopenFile();
		std::ofstream stream;
		tWString msFileName;
	public:
		cLogger(const tWString asFileName);
		~cLogger();
		void Dispose();
		void Print(const tString asMessage);
		void Clear();

		void SetFileName(const tWString asFile);

	};
	
	//extern void SetLogFile(const tString &asFile);
	extern void FatalError(const char* fmt, ...);
	extern void Error(const char* fmt, ...);
	extern void Warning(const char* fmt, ...);
	extern void Log(const char* fmt, ...);
	
	extern tString GetAbsolutePath();
	//extern void CreateMessageBox(const char* asCaption, const char *fmt, ...);
	//extern bool FileExists(const tString& asFileName);
	//extern void RemoveFile(const tString& asFileName);
	//extern bool CloneFile(const tString& asSrcFileName, const tString& asDestFileName, bool abFailIfExists);
	//extern bool CreateFolder(const tString& asPath);
	//extern bool FolderExists(const tString& asPath);
	//extern bool RenameFile(const tString& asFrom, const tString& asTo);	   
	//extern void SetWindowCaption(const tString &asName);  
	//extern bool HasWindowFocus(const tString &asWindowCaption);   
	//extern void Sleep(const unsigned int alMillisecs);

	class cLowLevelSystem
	{
		
	public:
		cLowLevelSystem();
		~cLowLevelSystem();

	};
}