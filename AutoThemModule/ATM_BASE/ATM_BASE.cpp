#include "stdafx.h"
#include "script.h"


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
	b_is_thread_safe = false;
	return true;
}