#include "LowLevelSystem.h"

#define _UNICODE
using namespace std;
namespace MGLE {
	////////////////////////////
	// Logger
	////////////////////////////
	string SetAbsolutePath();
	static string msAbsolutePath = SetAbsolutePath();
	static cLogger mLogger("MGLE.log");
	
	cLogger::cLogger(const string asFileName)
	{
		msFileName = GetAbsolutePath()+asFileName;
		cout << "New Logger: " << msFileName << endl;
	}
	cLogger::~cLogger()
	{
		if (mpFile) fclose(mpFile);
		delete mpFile;
	}
	void cLogger::Print(const string& asMessage)
	{
		if (!mpFile) ReopenFile();

		if (mpFile)
		{
			fprintf(mpFile, asMessage.c_str());
			fflush(mpFile);
			
		}
	}
	void cLogger::Clear()
	{
		ReopenFile();
		if (mpFile) fflush(mpFile);
	}
	void cLogger::SetFileName(const string asFile)
	{
		if (msFileName == asFile) return;

		msFileName = asFile;
		ReopenFile();
	}
	void cLogger::ReopenFile()
	{
		if (mpFile) fclose(mpFile);

#ifdef WIN32

		 fopen_s(&mpFile,msFileName.c_str(), ("w"));
#else
		mpFile = fopen(std::string::To8Char(msFileName).c_str(), "w");
#endif

	}
	////////////////////////////
	// Low Level System
	////////////////////////////
	cLowLevelSystem::cLowLevelSystem() {
		//mLogger.Clear();
		GetAbsolutePath();
	}
	cLowLevelSystem::~cLowLevelSystem() {

	}
	string SetAbsolutePath() {
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule != NULL)
		{
			//Get Wide
			WCHAR wpth[MAX_PATH];
			GetModuleFileName(hModule, wpth, (sizeof(wpth)));
			//Convert to string
			string spath = CW2A(wpth);
			//Convert to TCHAR
			TCHAR *cpath = new TCHAR[spath.size() + 1];
			cpath[spath.size()] = 0;
			copy(spath.begin(), spath.end(), cpath);
			PathRemoveFileSpec(cpath);
			//Convert back to string
			spath = CW2A(cpath);
			spath += '\\';
			delete cpath;
			//Finally
			return spath;
		}
		else
		{
			FatalError("Couldn't Set Relative Path; Module handle is NULL\n");
		}
	}
	string GetAbsolutePath() {
		return msAbsolutePath;
	}
	void Log(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		string sMess = "";
		sMess += text;
		cout << sMess;
		mLogger.Print(sMess);
	}
	void FatalError(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		string sMess = "FATAL ERROR: ";
		sMess += text;
		cout << sMess;
		mLogger.Print(sMess);

#ifdef WIN32
		//MessageBox(NULL, cString::To16Char(text).c_str(), _W("FATAL ERROR"), MB_ICONERROR);
#endif

		exit(1);
	}
	void Error(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		string sMess = "ERROR: ";
		sMess += text;
		cout << sMess;
		mLogger.Print(sMess);
	}
	void Warning(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		string sMess = "WARNING: ";
		sMess += text;
		cout << sMess;
		mLogger.Print(sMess);
	}
}