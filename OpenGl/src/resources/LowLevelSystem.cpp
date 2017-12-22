#include "LowLevelSystem.h"

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
		msFileName = GetAbsolutePath() + asFileName;
		time_t t = time(0);

		Log("--------------------------------------------------------\n");
		Log("MGLE ENGINE LOG : %i-%i-%i %i:%i:%i\n", localtime(&t)->tm_year + 1900, localtime(&t)->tm_mon + 1, localtime(&t)->tm_mday, localtime(&t)->tm_hour, localtime(&t)->tm_min, localtime(&t)->tm_sec);
		Log("--------------------------------------------------------\n");
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
			fprintf_s(mpFile, asMessage.c_str());
			cout << asMessage;
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

		fopen_s(&mpFile, msFileName.c_str(), ("w"));
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
		vsprintf_s(text, fmt, ap);
		va_end(ap);

		string sMess = "";
		sMess += text;

		mLogger.Print(sMess);

	}
	void FatalError(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf_s(text, fmt, ap);
		va_end(ap);

		string sMess = "";
		sMess += text;

#ifdef  WIN32
		string sBox = sMess + "\nSee log for details!";
		wstring wsTemp;
		size_t needed = mbstowcs(NULL, &sBox[0], 0);
		wsTemp.resize(needed);
		mbstowcs(&wsTemp[0], &sBox[0], needed);
		MessageBox(NULL, wsTemp.c_str(), (L"FATAL ERROR"), MB_ICONERROR);
#endif //  WIN32
		sMess = "FATAL ERROR: " + sMess;
		mLogger.Print(sMess);

		exit(1);
	}
	void Error(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf_s(text, fmt, ap);
		va_end(ap);

		string sMess = "ERROR: ";
		sMess += text;
		mLogger.Print(sMess);
	}
	void Warning(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;
		if (fmt == NULL)
			return;
		va_start(ap, fmt);
		vsprintf_s(text, fmt, ap);
		va_end(ap);

		string sMess = "WARNING: ";
		sMess += text;
		mLogger.Print(sMess);
	}
}
