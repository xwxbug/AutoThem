// Includes
/*
#include "StdAfx.h"								// Pre-compiled headers

#ifndef _MSC_VER								// Includes for non-MS compilers
	#include <windef.h>
#endif
#include <Psapi.h>
#include "AutoIt.h"								// Autoit values, macros and config options
#include "globaldata.h"
#include "utility.h"
*/
#include <windows.h>
#include <Psapi.h>
#include <stdio.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

///////////////////////////////////////////////////////////////////////////////
// WinMain()
///////////////////////////////////////////////////////////////////////////////
typedef int	(WINAPI* PATL_WinMain)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

bool get_interpreter_path(wchar_t* sz_module_path,wchar_t* sz_interpreter_path)
{
	wchar_t sz_current_interpreter_path[MAX_PATH] = { 0 };
	wcscpy(sz_current_interpreter_path, sz_module_path);
	wcscat(sz_current_interpreter_path, L"AutoThemLib.dll");
	if (GetFileAttributesW(sz_current_interpreter_path) != INVALID_FILE_ATTRIBUTES)
	{
		wcscpy(sz_interpreter_path, sz_module_path);
		return true;
	}
	else
	{
		HKEY hkResult;
		REGSAM regsam = KEY_READ;
		DWORD  dwDisp = 0;
		if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\AutoThem",NULL,NULL,NULL, regsam,NULL, &hkResult,&dwDisp)== ERROR_SUCCESS)
		{
			DWORD n_data_size=MAX_PATH;
			DWORD n_reg_type = 0;
			wchar_t sz_temp_path[MAX_PATH] = { 0 };
			if (RegQueryValueExW(hkResult, L"installpath", NULL,&n_reg_type,NULL,&n_data_size) != ERROR_SUCCESS)
			{
				RegCloseKey(hkResult);
				return false;
			}

			if (RegQueryValueExW(hkResult, L"installpath",NULL, &n_reg_type, (LPBYTE)sz_temp_path, &n_data_size)==ERROR_SUCCESS)
			{
				RegCloseKey(hkResult);
				wcscat(sz_temp_path, L"\\");
				wcscpy(sz_current_interpreter_path,sz_temp_path);
				wcscat(sz_current_interpreter_path, L"AutoThemLib.dll");
				if (GetFileAttributesW(sz_current_interpreter_path) != INVALID_FILE_ATTRIBUTES)
				{
					wcscpy(sz_interpreter_path, sz_temp_path);
					return true;
				}
				else
					return false;
			}
			else
			{
				RegCloseKey(hkResult);
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	wchar_t sz_script_path[MAX_PATH] = { 0 };
	wchar_t sz_script_name[MAX_PATH] = { 0 };
	wchar_t sz_dependent_path[MAX_PATH] = { 0 };
	wchar_t sz_interpreter_path[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, sz_script_path, MAX_PATH);
	wchar_t * str_ptr = wcsrchr(sz_script_path, L'\\');
	str_ptr[1] = 0;

	if (!get_interpreter_path(sz_script_path, sz_interpreter_path))
	{
		printf("interpreter not exist!!!\n");
		return -1;
	}

	wcscpy(sz_dependent_path, sz_interpreter_path);
	wcscat(sz_interpreter_path, L"AutoThemLib.dll");
	wcscat(sz_dependent_path, L"dependency");
	AddDllDirectory(sz_dependent_path);
	GetModuleBaseNameW(GetCurrentProcess(), NULL, sz_script_name, MAX_PATH);
	str_ptr = wcsrchr(sz_script_name, L'.');
	if (!str_ptr)
		return -1;

	wcscpy(str_ptr, L".at");
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

	HMODULE h_interpreter = LoadLibraryW(sz_interpreter_path);
	if (!h_interpreter)
		return -9;

	PATL_WinMain ATL_WinMain = (PATL_WinMain)GetProcAddress(h_interpreter, "ATL_WinMain");
	if (!ATL_WinMain)
		return -10;

	int n_result = ATL_WinMain(hInstance, nullptr, lp_sz_cmdLine, nCmdShow);
	delete[]lp_sz_cmdLine;
	FreeLibrary(h_interpreter);
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
	wchar_t sz_dependent_path[MAX_PATH] = { 0 };
	wchar_t sz_interpreter_path[MAX_PATH] = { 0 };

	GetModuleFileNameW(NULL, sz_script_path, MAX_PATH);
	wchar_t * str_ptr = wcsrchr(sz_script_path, L'\\');
	str_ptr[1] = 0;

	if (!get_interpreter_path(sz_script_path, sz_interpreter_path))
	{
		printf("interpreter not exist!!!\n");
		return -1;
	}

	wcscpy(sz_dependent_path, sz_interpreter_path);
	wcscat(sz_interpreter_path, L"AutoThemLib.dll");
	wcscat(sz_dependent_path, L"dependency");
	GetModuleBaseNameW(GetCurrentProcess(), NULL, sz_script_name, MAX_PATH);
	str_ptr = wcsrchr(sz_script_name, L'.');
	if (!str_ptr)
		return -1;
	
	wcscpy(str_ptr, L".at");
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

	HMODULE h_interpreter = LoadLibraryW(sz_interpreter_path);
	if (!h_interpreter)
		return -9;
	
	PATL_WinMain ATL_WinMain = (PATL_WinMain)GetProcAddress(h_interpreter, "ATL_WinMain");
	if (!ATL_WinMain)
		return -10;
	
	int n_result= ATL_WinMain(hModule, nullptr, lpCmdLine, si.wShowWindow);
	delete[]lpCmdLine;
	FreeLibrary(h_interpreter);
	return n_result;
}