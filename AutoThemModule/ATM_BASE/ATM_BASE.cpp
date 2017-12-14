#include "stdafx.h"
#include "script.h"


AUT_RESULT V_MessageBox(VectorVariant &vParams, Variant &vResult)
{
	MessageBoxW(0, L"WTF", L"JUST TEST", 0);

	return 0;
}


bool ATE_REGISTER_MODULE(void* LPREGISTER_MODULE_FUNC)
{
	IExternalScript* ies = (IExternalScript*)LPREGISTER_MODULE_FUNC;
	ATE_FuncInfo afi;
	afi.lpFunc = V_MessageBox;
	afi.nMax = 5;
	afi.nMin = 0;
	afi.szName = "MessageBox";
	ies->RegisterModuleFuncs(&afi);
	afi.szName = "MessageBox1";
	ies->RegisterModuleFuncs(&afi);
	return true;
}