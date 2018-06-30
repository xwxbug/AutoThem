#include "stdafx.h"
#include "script.h"
#include "utility.h"

AUT_RESULT V_AutoThemModuleTest(VectorVariant &vParams, Variant &vResult)
{
	if (vParams.size())
	{
		MessageBoxW(0, vParams[0].szValue(), L"JUST TEST", 0);
	}
	else
	{
		MessageBoxW(0, L"WTF", L"JUST TEST", 0);
	}
	
	vResult = AUT_OK;
	return 0;
}

AUT_RESULT F_Beep(VectorVariant &vParams, Variant &vResult)
{
	unsigned long n_Freq = 500;
	unsigned long n_Duration = 1000;
	if (vParams.size() > 0)
		n_Freq = vParams[0].nValue();
	if (vParams.size() > 1)
		n_Duration = vParams[1].nValue();
	Beep(n_Freq, n_Duration);
	vResult = AUT_OK;
	return 0;
}

AUT_RESULT F_ConsolePause(VectorVariant &vParams, Variant &vResult)
{
	system("pause");
	return AUT_OK;
}

AUT_RESULT F_ConsoleGetTitle(VectorVariant &vParams, Variant &vResult)
{
	wchar_t sz_title[MAX_PATH];
	GetConsoleTitleW(sz_title,MAX_PATH);
	vResult = sz_title;
	return AUT_OK;
}

AUT_RESULT F_ConsoleSetTitle(VectorVariant &vParams, Variant &vResult)
{
	SetConsoleTitleW(vParams[0].szValue());
	return AUT_OK;
}

//////////////////////////////////////////////////////////////////////////
// F_ConsoleWrite("text")
//
// Writes to the console so editors like SciTE can
// read the data
//////////////////////////////////////////////////////////////////////////
AUT_RESULT F_ConsoleWrite(VectorVariant &vParams, Variant &vResult)
{
	printf("%s", Util_UNICODEtoANSIStr(vParams[0].szValue()).c_str());
	fflush(stdout);
	return AUT_OK;

}	// F_ConsoleWrite()


AUT_RESULT F_ConsoleWriteError(VectorVariant &vParams, Variant &vResult)
{
	fprintf(stderr,"%s", Util_UNICODEtoANSIStr(vParams[0].szValue()).c_str());
	fflush(stderr);
	return AUT_OK;

}


bool ATE_REGISTER_MODULE(void* LPREGISTER_MODULE_FUNC,bool &b_is_thread_safe)
{
	IExternalScript* ies = (IExternalScript*)LPREGISTER_MODULE_FUNC;
	ATE_FuncInfo afi;
	afi.lpFunc = V_AutoThemModuleTest;
	afi.nMax = 5;
	afi.nMin = 0;
	afi.szName = "AutoThemModuleTest";
	ies->RegisterModuleFuncs(&afi);
	ies->RegisterModuleFuncs("BEEP",F_Beep,0,2);
	ies->RegisterModuleFuncs("CONSOLEGETTITLE", F_ConsoleGetTitle, 0, 0);
	ies->RegisterModuleFuncs("CONSOLEPAUSE", F_ConsolePause, 0, 0);
	ies->RegisterModuleFuncs("CONSOLESETTITLE", F_ConsoleSetTitle, 1, 1);
	ies->RegisterModuleFuncs("CONSOLEWRITE", F_ConsoleWrite, 1, 1);
	ies->RegisterModuleFuncs("CONSOLEWRITEERROR", F_ConsoleWriteError, 1, 1);
	b_is_thread_safe = false;
	return true;
}