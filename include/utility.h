#ifndef __UTIL_H
#define __UTIL_H

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
// utility.h
//
// This file contains the includes for the utility library.  Simple functions
// that can be called at will to perform useful functions.
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#ifndef _MSC_VER								// Includes for non-MS compilers
	#include <stdio.h>
	#include <windows.h>
#endif

#include "variant_datatype.h"
#include <string>

// Function declarations
void	Util_FatalError(UINT iErrTitle, UINT iErrMsg, HWND hWnd);
void	Util_FatalError(char *szTitle, char *szText, HWND hWnd);
int		Util_NewHandler( size_t size);

void	Util_RandInit(void);

void	Util_RegReadString(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwBufLen, LPWSTR szValue);
void	Util_RegReadString(HKEY hKey, LPCSTR  lpSubKey, LPCSTR  lpValueName, DWORD dwBufLen, LPSTR  szValue);
void	Util_WinKill(HWND hWnd);

bool	Util_DoesProcessExist(const char *szName, DWORD &dwPid, bool &bResult);
bool	Util_DoesProcessExist9x2000(const char *szName, DWORD &dwPid, bool &bResult);
bool	Util_DoesProcessExistNT(const char *szName, DWORD &dwPid, bool &bResult);

int		Util_MessageBoxEx(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uTimeout);
unsigned int _stdcall Util_TimeoutMsgBoxThread(void *pParam);
BOOL	CALLBACK Util_FindMsgBoxProc(HWND hwnd, LPARAM lParam);

void	Util_StripCR(char *		szText);
void	Util_StripCR(wchar_t *	szText);
void	Util_AddCR(const char *szInput, char *szOutput);
void	Util_AddCR(const wchar_t *szInput, wchar_t *szOutput);
unsigned int Util_AddCRSize(const char *	szText);
unsigned int Util_AddCRSize(const wchar_t *	szText);

void	Util_StripTrailingDir(char*		szPath);
void	Util_StripTrailingDir(wchar_t*	szPath);

bool	Util_GetFileVersion(char *		szFile, char *		szVersion);
bool	Util_GetFileVersion(wchar_t *	szFile, wchar_t *	szVersion);

bool	Util_DoesFileExist(const char *		szFilename);
bool	Util_DoesFileExist(const wchar_t *	szFilename);
bool	Util_IsDir(const char *		szPath);
bool	Util_IsDir(const wchar_t *	szPath);
void	Util_GetFullPathName(const char*	szIn, char*		szOut);
void	Util_GetFullPathName(const wchar_t* szIn, wchar_t*	szOut);
bool	Util_GetLongFileName(const char*	szIn, char*		szOut);
bool	Util_GetLongFileName(const wchar_t* szIn, wchar_t*	szOut);
bool	Util_IsDifferentVolumes(const char *szPath1, const char *szPath2);
bool	Util_IsDifferentVolumes(const wchar_t *szPath1, const wchar_t *szPath2);
bool	Util_DeleteFile(const char *szFilename);
bool	Util_FileSetTime(const char *szFilename, FILETIME *ft, int nWhichTime);
bool	Util_CopyFile(const char *szInputSource, const char *szInputDest, bool bOverwrite, bool bMove);
void	Util_ExpandFilenameWildcard(const char *szSource, const char *szDest, char *szExpandedDest);
void	Util_ExpandFilenameWildcardPart(const char *szSource, const char *szDest, char *szExpanded);
bool	Util_CreateDir(const wchar_t *szDirName);
bool	Util_RemoveDir(const char *		szInputSource, bool bRecurse);
bool	Util_RemoveDir(const wchar_t *	szInputSource, bool bRecurse);
bool	Util_CopyDir (const wchar_t *szInputSource, const wchar_t *szInputDest, bool bOverwrite);
bool	Util_MoveDir (const wchar_t *szInputSource, const wchar_t *szInputDest, bool bOverwrite);

void	Util_AddTextToBuffer(const char *szText, char *szBuffer, unsigned int iBufSize);

const char * Util_GetWinText(HWND hWnd, bool bDetectHiddenText);
BOOL	CALLBACK Util_GetWinTextProc(HWND hWnd, LPARAM lParam);
const char * Util_GetClassList(HWND hWnd);
BOOL	CALLBACK Util_GetClassListProc(HWND hWnd, LPARAM lParam);

void	Util_GetIPAddress(int nAdapter, char *szInetBuf);

void	Util_VariantArrayDim(Variant *pvVariant, unsigned int iElements);
Variant * Util_VariantArrayGetRef(Variant *pvVariant, unsigned int iElement);

void	Util_SoundPlay(const wchar_t *szFilename, bool bWait);

BOOL	Util_Shutdown(int nFlag);
BOOL	Util_ShutdownHandler(HWND hwnd, DWORD lParam);

bool	Util_GetInt(const char *szInt, int &pos, int &nValue);
bool	Util_ConvHex(const UINT uVal, char *szBuffer, const int iDigits);
bool	Util_ConvDec(const char *		szHex, int &nDec);
bool	Util_ConvDec(const wchar_t *	szHex, int &nDec);
bool	Util_IsWinHung(HWND hWnd, UINT nTimeOut = 5000);
void	Util_AttachThreadInput(HWND hWnd, bool bAttach);

int		Util_MouseDown(const char *szButton);
int		Util_MouseDown(const wchar_t *szButton);
int 	Util_MouseUp(const char *szButton);
int 	Util_MouseUp(const wchar_t *szButton);
int		Util_MouseWheel(const char *szDirection);
int		Util_MouseWheel(const wchar_t *szDirection);
bool	Util_DownloadFile(const char *szUrl, const char *szOutFile, bool &bFatal);

void	Util_Strncpy(char *szBuffer, const char *szString, int nBufSize);
char *	Util_fgetsb(char *szBuffer, int nBufSize, FILE *fptr);
void	Util_Sleep(int nTimeOut);
int		Util_WinPrintf(const char *szTitle, const char *szFormat, ...);

void	Util_BGRtoRGB(int &nCol);
void	Util_RGBtoBGR(int &nCol);

#ifdef _DEBUG
	void Util_DebugMsg(const char *szFormat, ...);
#endif

char *		Util_StrCpyAlloc(const char *		szSource);
wchar_t *	Util_StrCpyAlloc(const wchar_t *	szSource);

HICON	Util_LoadIcon(int nID, int nWidth, int nHeight, int nDepth);
bool	Util_ConvSystemTime(const char *szTime, SYSTEMTIME *st, bool bDate, int nSep);

int		Util_IsSpace(int c);

wchar_t * Util_ANSItoUNICODE(const char *szANSI, int nMinLen = 0);
std::wstring Util_ANSItoUNICODEStr(const char *szANSI, int nMinLen=0);

char *	Util_UNICODEtoANSI(const wchar_t *szUNI, int nMinLen = 0);
std::string Util_UNICODEtoANSIStr(const wchar_t *szUNI, int nMinLen=0);

size_t Util_find_string_in_str(const wchar_t* sz_text, const wchar_t *szInput, bool bCaseSense, int nOccurance=1);

std::string stringtolowerA(std::string str);
std::wstring stringtolowerW(std::wstring str);
std::string stringtoupperA(std::string str);
std::wstring stringtoupperW(std::wstring str);

template<typename T> inline void Util_VariantArrayAssign(Variant *pvVariant, unsigned int iElement, T tParam)
{
	Variant *pvTemp = Util_VariantArrayGetRef(pvVariant, iElement);
	*pvTemp = tParam;
}	// Util_VariantArrayAssign()

template<typename T> inline void Util_Variant2DArrayAssign(Variant *pvVariant, unsigned int iElement0, unsigned int iElement1, T tParam)
{
	Variant *pvTemp;
	pvVariant->ArraySubscriptClear();	// Reset the subscript
	pvVariant->ArraySubscriptSetNext(iElement0);	// First dimension
	pvVariant->ArraySubscriptSetNext(iElement1);	// Second dimension
	pvTemp	= pvVariant->ArrayGetRef();	// Get reference to the element
	*pvTemp = tParam;		// Assign parameter
}	// Util_Variant2DArrayAssign()


///////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_H

