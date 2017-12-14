// Includes
#include "StdAfx.h"								// Pre-compiled headers

#ifndef _MSC_VER								// Includes for non-MS compilers
	#include <windef.h>
#endif
#include <Psapi.h>
#include "AutoIt.h"								// Autoit values, macros and config options
#include "globaldata.h"
#include "utility.h"


///////////////////////////////////////////////////////////////////////////////
// WinMain()
///////////////////////////////////////////////////////////////////////////////

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	wchar_t sz_script_path[MAX_PATH] = { 0 };
	wchar_t sz_script_name[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, sz_script_path, MAX_PATH);
	wchar_t * str_ptr = wcsrchr(sz_script_path, L'\\');
	str_ptr[1] = 0;
	GetModuleBaseNameW(GetCurrentProcess(), NULL, sz_script_name, MAX_PATH);
	str_ptr = wcsrchr(sz_script_name, L'.');
	if (!str_ptr)
		return -1;

	wcscpy(str_ptr, L".au3");
	wcscat(sz_script_path, sz_script_name);

	if (GetFileAttributesW(sz_script_path) == INVALID_FILE_ATTRIBUTES)
	{
		printf("script file not exist!!!\n");
		return -1;
	}

	wchar_t* lp_sz_cmdLine = new wchar_t[4097]();

	wcscat(lp_sz_cmdLine, L"\"");
	wcscat(lp_sz_cmdLine, sz_script_path);
	wcscat(lp_sz_cmdLine, L"\" ");
	wcscat(lp_sz_cmdLine, lpCmdLine);

	int n_result = ATL_WinMain(hInstance, nullptr, lp_sz_cmdLine,nCmdShow);
	delete[]lp_sz_cmdLine;
	return n_result;
} // Winmain()

int wmain(int argc, wchar_t* argv[])
{
	HMODULE hModule;
	STARTUPINFOW si = {0};
	si.cb = sizeof STARTUPINFOW;
	hModule = GetModuleHandleW(NULL);
	GetStartupInfoW(&si);

	wchar_t sz_script_path[MAX_PATH] = { 0 };
	wchar_t sz_script_name[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, sz_script_path, MAX_PATH);
	wchar_t * str_ptr = wcsrchr(sz_script_path, L'\\');
	str_ptr[1] = 0;
	GetModuleBaseNameW(GetCurrentProcess(), NULL, sz_script_name, MAX_PATH);
	str_ptr = wcsrchr(sz_script_name, L'.');
	if (!str_ptr)
		return -1;
	
	wcscpy(str_ptr, L".au3");
	wcscat(sz_script_path, sz_script_name);

	if (GetFileAttributesW(sz_script_path)==INVALID_FILE_ATTRIBUTES)
	{
		printf("script file not exist!!!\n");
		return -1;
	}

	wchar_t* lpCmdLine = new wchar_t[4097]();

	wcscat(lpCmdLine, L"\"");
	wcscat(lpCmdLine, sz_script_path);
	wcscat(lpCmdLine, L"\" ");


	for (size_t i=1;i<argc;i++)
	{
		wcscat(lpCmdLine, L"\"");
		wcscat(lpCmdLine, argv[i]);
		wcscat(lpCmdLine, L"\" ");
	}
	int n_result= ATL_WinMain(hModule, nullptr, lpCmdLine, si.wShowWindow);
	delete[]lpCmdLine;
	return n_result;
}