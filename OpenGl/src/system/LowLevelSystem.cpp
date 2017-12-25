#include "LowLevelSystem.h"

using namespace std;
namespace MGLE {
	////////////////////////////
	// Logger
	////////////////////////////
	string SetAbsolutePath();
	static string msAbsolutePath = SetAbsolutePath();
	static cLogger mLogger(L"MGLE.log");

	cLogger::cLogger(const tWString asFileName)
	{
		msFileName =cString::To16( GetAbsolutePath()) + asFileName;
		time_t t = time(0);

		Log("--------------------------------------------------------\n");
		Log("MGLE ENGINE LOG : %i-%i-%i %i:%i:%i\n", localtime(&t)->tm_year + 1900, localtime(&t)->tm_mon + 1, localtime(&t)->tm_mday, localtime(&t)->tm_hour, localtime(&t)->tm_min, localtime(&t)->tm_sec);
		Log("--------------------------------------------------------\n");
	}
	void cLogger::Dispose() {

	}
	cLogger::~cLogger()
	{
		Dispose();
	}
	
	void cLogger::Print(const tString asMessage)
	{
		
		if (!stream.is_open()) ReopenFile();

		if (stream.is_open())
		{
			stream << asMessage;
			cout << asMessage;
			stream.flush();
		}
	}
	void cLogger::Clear()
	{
		ReopenFile();
		if (stream.is_open()) stream.flush();
	}
	void cLogger::SetFileName(const tWString asFile)
	{
		if (msFileName == asFile) return;

		msFileName = asFile;
		ReopenFile();
	}
	void cLogger::ReopenFile()
	{
		if (stream.is_open()) stream.close();

		stream.open(msFileName.c_str());

	}
	////////////////////////////
	// Low Level System
	////////////////////////////
	cLowLevelSystem::cLowLevelSystem() {
		//mLogger.Clear();
		GetAbsolutePath();
	}
	cLowLevelSystem::~cLowLevelSystem() {
		mLogger.Dispose();
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
		sMess = "FATAL ERROR: " + sMess + "\n--------------------------------------------------------\nExit Failure!\n";
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
