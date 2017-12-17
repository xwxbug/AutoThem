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


///////////////////////////////////////////////////////////////////////////////
// Asc()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_Asc(VectorVariant &vParams, Variant &vResult)
{
	vResult = int(uchar(vParams[0].szValue()[0]));
	return AUT_OK;
} // Asc()


///////////////////////////////////////////////////////////////////////////////
// AscW()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_AscW(VectorVariant &vParams, Variant &vResult)
{
	vResult = int(unsigned short(vParams[0].szValue()[0]));
	return AUT_OK;
} // AscW()


///////////////////////////////////////////////////////////////////////////////
// ASin()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_ASin(VectorVariant &vParams, Variant &vResult)
{
	vResult = asin(vParams[0].fValue());
	return AUT_OK;
} // ASin()


///////////////////////////////////////////////////////////////////////////////
// ATan()
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT F_ATan(VectorVariant &vParams, Variant &vResult)
{

	vResult = atan(vParams[0].fValue());
	return AUT_OK;

} // ATan()

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
	ies->RegisterModuleFuncs("ASC", F_Asc, 1, 1);
	ies->RegisterModuleFuncs("ASCW", F_AscW, 1, 1);
	ies->RegisterModuleFuncs("ASIN", F_ASin, 1, 1);
	ies->RegisterModuleFuncs("ATAN", F_ATan, 1, 1);
	b_is_thread_safe = false;
	return true;
}