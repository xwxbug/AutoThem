#include "stdafx.h"
#include "script.h"


///////////////////////////////////////////////////////////////////////////////
// Abs()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_Abs(VectorVariant &vParams, Variant &vResult)
{
	//
	vResult = fabs(vParams[0].fValue());
	return AUT_OK;
} // Abs()


///////////////////////////////////////////////////////////////////////////////
// ACos()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_ACos(VectorVariant &vParams, Variant &vResult)
{
	vResult = acos(vParams[0].fValue());
	return AUT_OK;
} // ACos()


bool ATE_REGISTER_MODULE(void* LPREGISTER_MODULE_FUNC,bool &b_is_thread_safe)
{
	IExternalScript* ies = (IExternalScript*)LPREGISTER_MODULE_FUNC;
/*
	ATE_FuncInfo afi;
	afi.lpFunc = V_AutoThemModuleTest;
	afi.nMax = 5;
	afi.nMin = 0;
	afi.szName = "AutoThemModuleTest";
	ies->RegisterModuleFuncs(&afi);
*/
	ies->RegisterModuleFuncs("ABS", F_Abs, 1, 1);
	ies->RegisterModuleFuncs("ACOS", F_ACos, 1, 1);
	b_is_thread_safe = false;
	return true;
}