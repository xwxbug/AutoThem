
///////////////////////////////////////////////////////////////////////////////
//
// AutoIt v3
//
// Copyright (C)1999-2005:
//		- Jonathan Bennett <jon at hiddensoft dot com>
//		- See "AUTHORS.txt" for contributors.
//
// This file is part of AutoIt.
//
// AutoIt source code is copyrighted software distributed under the terms of the
// AutoIt source code license.
//
// You may:
//
// - Customize the design and operation of the AutoIt source code to suit
// the internal needs of your organization except to the extent not
// permitted in this Agreement
//
// You may not:
//
// - Distribute the AutoIt source code and/or compiled versions of AutoIt
// created with the AutoIt source code.
// - Create derivative works based on the AutoIt source code for distribution
// or usage outside your organisation.
// - Modify and/or remove any copyright notices or labels included in the
// AutoIt source code.
//
// AutoIt is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// See the LICENSE.txt file that accompanies the AutoIt source
// code for more details.
//
///////////////////////////////////////////////////////////////////////////////
//
// AutoIt.cpp
//
// The main entry point to the program.  This file also creates the pre-compiled
// header files.
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"								// Pre-compiled headers

#ifndef _MSC_VER								// Includes for non-MS compilers
	#include <windef.h>
#endif

#include "AutoIt.h"								// Autoit values, macros and config options
#include "globaldata.h"
#include "utility.h"


///////////////////////////////////////////////////////////////////////////////
// WinMain()
///////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return ATL_WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
} // Winmain()

int main(int argc, char* argv[])
{
	HMODULE hModule;
	STARTUPINFOW si = {0};
	si.cb = sizeof STARTUPINFOW;
	hModule = GetModuleHandleW(NULL);
	GetStartupInfoW(&si);

	char* lpCmdLine = new char[4097]();
	for (size_t i=1;i<argc;i++)
	{
		strcat(lpCmdLine, "\"");
		strcat(lpCmdLine, argv[i]);
		strcat(lpCmdLine, "\" ");
	}
	int n_result= ATL_WinMain(hModule, nullptr, lpCmdLine, si.wShowWindow);
	delete[]lpCmdLine;
	return n_result;
}