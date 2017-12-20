#pragma once
#include "stdafx.h"
#include <windows.h>
#include "MGLE.h"


namespace MGLE {
	class cLogger
	{
	public:
		cLogger(const std::string asDefaultFile);
		~cLogger();

		void Print(const std::string& asMessage);
		void Clear();

		void SetFileName(const std::string asFile);

	private:
		void ReopenFile();

		FILE *mpFile;
		std::string msFileName;
	};
	
	//extern void SetLogFile(const std::string &asFile);
	extern void FatalError(const char* fmt, ...);
	extern void Error(const char* fmt, ...);
	extern void Warning(const char* fmt, ...);
	extern void Log(const char* fmt, ...);
	
	extern std::string GetAbsolutePath();
	//extern void CreateMessageBox(const char* asCaption, const char *fmt, ...);
	//extern bool FileExists(const std::string& asFileName);
	//extern void RemoveFile(const std::string& asFileName);
	//extern bool CloneFile(const std::string& asSrcFileName, const std::string& asDestFileName, bool abFailIfExists);
	//extern bool CreateFolder(const std::string& asPath);
	//extern bool FolderExists(const std::string& asPath);
	//extern bool RenameFile(const std::string& asFrom, const std::string& asTo);	   
	//extern void SetWindowCaption(const std::string &asName);  
	//extern bool HasWindowFocus(const std::string &asWindowCaption);   
	//extern void Sleep(const unsigned int alMillisecs);

	class cLowLevelSystem
	{
		
	public:
		cLowLevelSystem();
		~cLowLevelSystem();

	};
}