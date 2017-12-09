
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
// cmdline.cpp
//
// A standalone class to make reading command line options a little easier.
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"								// Pre-compiled headers

#ifndef _MSC_VER								// Includes for non-MS compilers
	#include <stdio.h>
	#include <string.h>
#endif

#include "cmdline.h"
#include "utility.h"


///////////////////////////////////////////////////////////////////////////////
// Constructor()
///////////////////////////////////////////////////////////////////////////////

CmdLine::CmdLine()
{
	m_nCurrentParam	= 0;						// Current param to return for GetNextParam()
}


///////////////////////////////////////////////////////////////////////////////
// Destructor()
///////////////////////////////////////////////////////////////////////////////

CmdLine::~CmdLine()
{
	Reset();

}


///////////////////////////////////////////////////////////////////////////////
// SetCmdLine()
///////////////////////////////////////////////////////////////////////////////

void CmdLine::SetCmdLine(std::wstring szCmdLine)
{
	Reset();									// Reset any previous command lines

	// Store the raw command line
	m_szCmdLineRaw = szCmdLine;

	// Command line parameters are separated by spaces
	// If spaces are required in a parameter, it should be surrounded by quotes
	// If quotes are required, they must be doubled up eg "" is one quote

	size_t		i = 0;							// In string position
	size_t		iParam = 0;						// Out param position
	bool		bQuote = false;					// Quoting is inactive
	wchar_t		szParam[CMDLINE_MAXLEN+1];		// Store our temp parameter
	wchar_t		ch;

	// Whenever we hit a space and we are NOT in quote mode
	// - Store param
	// - Skip spaces

	// Skip leading spaces
	while ( (ch = szCmdLine[i]) == L' ' || ch  == L'\t')
		i++;

	while ( ((ch = szCmdLine[i++]) != L'\0')  &&  (iParam < CMDLINE_MAXLEN) )
	{
		if ( ch == L' '|| ch  == L'\t')
		{
			// Param separator found - are we in quote mode?
			if ( bQuote == true )
			{
				szParam[iParam++] = ch;			// Store as normal - not param separator
			}
			else
			{
				szParam[iParam] = '\0';
				StoreParam(szParam);
				iParam = 0;
				// We are starting a param, skip all spaces
				while ( (ch = szCmdLine[i]) == L' '|| ch  == L'\t' )
					i++;
			}
		}
		else
		{
			if ( ch == L'"' )
			{
				if (szCmdLine[i] == L'"')
				{
					szParam[iParam++] = L'"';
					i++;
				}
				else
					bQuote = !bQuote;					// Quote found - toggle quote mode
			}
			else
				szParam[iParam++] = ch;				// Simply store character
		}

	} // End While

	// Check iParam, if there was a construct in progress, finish and store
	if ( iParam != 0 )
	{
		szParam[iParam] = '\0';
		StoreParam(szParam);
	}


} // SetCmdLine()


std::wstring CmdLine::GetCmdLine()
{
	return m_szCmdLineRaw;
}

size_t CmdLine::GetNumParams(void) const
{
	return m_vec_sz_params.size();
}

///////////////////////////////////////////////////////////////////////////////
// StoreParam()
///////////////////////////////////////////////////////////////////////////////

void CmdLine::StoreParam(wchar_t *szParam)
{
	m_vec_sz_params.push_back(szParam);
} // StoreParam()

///////////////////////////////////////////////////////////////////////////////
// Reset()
///////////////////////////////////////////////////////////////////////////////

void CmdLine::Reset(void)
{
	m_nCurrentParam		= 0;
	m_vec_sz_params.clear();
} // Reset()


///////////////////////////////////////////////////////////////////////////////
// GetParam()
///////////////////////////////////////////////////////////////////////////////

bool CmdLine::GetParam(size_t nParam, char *szParam) const
{
	// Ensure we don't pass back crap if there is an error
	szParam[0] = '\0';

	if (nParam >= m_vec_sz_params.size())
		return false;							// Invalid request
	else
	{
		strcpy(szParam, Util_UNICODEtoANSIStr(m_vec_sz_params[nParam].c_str()).c_str());
		return true;
	}
} // GetParam()


std::wstring CmdLine::GetParam(size_t nParam) const
{
	if (nParam >= m_vec_sz_params.size())
		return L"";								// Invalid request
	else
		return m_vec_sz_params[nParam];
}

///////////////////////////////////////////////////////////////////////////////
// GetNextParam()
///////////////////////////////////////////////////////////////////////////////

bool CmdLine::GetNextParam(char *szParam)
{
	// Ensure we don't pass back crap if there is an error
	szParam[0] = '\0';

	if (m_nCurrentParam >= m_vec_sz_params.size())
		return false;							// Invalid request
	else
	{
		strcpy(szParam, Util_UNICODEtoANSIStr(m_vec_sz_params[m_nCurrentParam].c_str()).c_str());
		m_nCurrentParam++;
		return true;
	}
} // GetNextParam()

std::wstring CmdLine::GetNextParam()
{
	std::wstring sz_result;
	if (m_nCurrentParam >= m_vec_sz_params.size())
		return sz_result;							// Invalid request
	else
	{
		sz_result=m_vec_sz_params[m_nCurrentParam];
		m_nCurrentParam++;
		return sz_result;
	}
}

void CmdLine::GetNextParamReset(void)
{
	m_nCurrentParam = 0;
}
