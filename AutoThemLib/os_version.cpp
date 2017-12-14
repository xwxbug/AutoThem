#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#pragma warning(disable:4996) 

#include <Windows.h>
#include <stdio.h>
#include "os_version.h"

OS_Version::OS_Version()
{
	typedef NTSTATUS( NTAPI* fnRtlGetVersion )(PRTL_OSVERSIONINFOEXW lpVersionInformation);
	static fnRtlGetVersion RtlGetVersion;

	// Get details of the OS we are running on
	OSvi.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);
	RtlGetVersion = (fnRtlGetVersion)GetProcAddress(GetModuleHandleW( L"ntdll.dll" ),"RtlGetVersion" );
	if (RtlGetVersion)	
		RtlGetVersion(&OSvi);	
	else	
		GetVersionExW((LPOSVERSIONINFOW)&OSvi);

	// Populate Major and Minor version numbers
	m_dwMajorVersion	= OSvi.dwMajorVersion;
	m_dwMinorVersion	= OSvi.dwMinorVersion;
	m_dwBuildNumber		= OSvi.dwBuildNumber;

	// Get CSD information
	size_t nTemp = wcslen(OSvi.szCSDVersion);

	if (nTemp > 0)
	{
		size_t i=0;
		//	strip trailing
		for ( i=nTemp-1; i>0; i--)
		{
			if (OSvi.szCSDVersion[i] != L' ')
				break;
			OSvi.szCSDVersion[i] = L'\0';
		}

		//	strip leading
		nTemp = i;
		for (i=0; i<nTemp; i++)
		{
			if (OSvi.szCSDVersion[i] != L' ')
				break;
		}
		wcscpy(m_szCSDVersion, &OSvi.szCSDVersion[i]);
	}
	else
		m_szCSDVersion[0] = 0;				// No CSD info, make it blank to avoid errors
	wcscpy(	m_szOperatingSystemName,L"Unknow Operating System Name");
	_swprintf(m_szOperatingSystemShortName,L"%d.%d",OSvi.dwMajorVersion,OSvi.dwMinorVersion);
	// Set all options to false by default
	m_bWin2000		= false;	m_bWin2000orLater	= false;
	m_bWinXP		= false;	m_bWinXPorLater		= false;
	m_bWin2003		= false;	m_bWin2003orLater	= false;
	m_bWinVista		= false;	m_bWinVistaorLater	= false;
	m_bWin2008		= false;	m_bWin2008orLater	= false;
	m_bWin7			= false;	m_bWin7orLater		= false;
	m_bWin2008R2	= false;	m_bWin2008R2orLater = false;
	m_bWin8			= false;	m_bWin8orLater		= false;
	m_bWin2012		= false;	m_bWin2012orLater	= false;
	m_bWin8_1		= false;	m_bWin8_1orLater	= false;
	m_bWin2012R2	= false;	m_bWin2012R2orLater	= false;
	m_bWin10		= false;	m_bWin10orLater		= false;
	m_bWin2016		= false;	m_bWin2016orLater	= false;
	// Work out if NT or 9x
	if (OSvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		switch (m_dwMajorVersion)
		{
		case 5:	
			{
				if ( m_dwMinorVersion == 0 )		// Win 2000
				{
					m_bWin2000 = m_bWin2000orLater = true;
					wcscpy(	m_szOperatingSystemName,L"Microsoft Windows 2000");
					wcscpy(	m_szOperatingSystemShortName,L"2000");
				}
				else if ( m_dwMinorVersion == 1 )		// WinXP
				{
					m_bWinXP = m_bWin2000orLater = m_bWinXPorLater = true;
					wcscpy(	m_szOperatingSystemName,L"Microsoft Windows XP");
					wcscpy(	m_szOperatingSystemShortName,L"XP");
				}
				else if (m_dwMinorVersion == 2)		// 2003
				{
					m_bWin2003 = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater;
					wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2003");
					wcscpy(	m_szOperatingSystemShortName,L"2003");
				}
				break;
			}
		case 6:
			{
				if ( m_dwMinorVersion == 0 )		// vista
				{
					if (OSvi.wProductType==VER_NT_WORKSTATION)						
					{
						m_bWinVista = m_bWin2000orLater =  m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Vista");
						wcscpy(	m_szOperatingSystemShortName,L"Vista");
					}
					else
					{
						m_bWin2008  = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2008");
						wcscpy(	m_szOperatingSystemShortName,L"2008");
					}
				}
				else if (m_dwMinorVersion==1)
				{
					if (OSvi.wProductType==VER_NT_WORKSTATION)
					{
						m_bWin7 = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows 7");
						wcscpy(	m_szOperatingSystemShortName,L"7");
					}
					else
					{
						m_bWin2008R2  = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2008 R2");
						wcscpy(	m_szOperatingSystemShortName,L"2008R2");
					}
				}
				else if (m_dwMinorVersion==2)
				{
					if (OSvi.wProductType==VER_NT_WORKSTATION)						
					{
						m_bWin8 = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin8orLater=m_bWin2012orLater=true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows 8");
						wcscpy(	m_szOperatingSystemShortName,L"8");
					}
					else
					{
						m_bWin2012  = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin8orLater=m_bWin2012orLater=true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2012");
						wcscpy(	m_szOperatingSystemShortName,L"2012");
					}
				}
				else if (m_dwMinorVersion==3)
				{
					if (OSvi.wProductType==VER_NT_WORKSTATION)						
					{
						m_bWin8_1 = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin8orLater=m_bWin2012orLater= m_bWin8_1orLater=m_bWin2012R2orLater =true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows 8.1");
						wcscpy(	m_szOperatingSystemShortName,L"8.1");
					}
					else
					{
						m_bWin2012R2  = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin8orLater=m_bWin2012orLater= m_bWin8_1orLater=m_bWin2012R2orLater =true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2012 R2");
						wcscpy(	m_szOperatingSystemShortName,L"2012R2");
					}
				}
				break;
			}
		case  10:
			{
				if (m_dwMinorVersion>=0)
				{
					if (OSvi.wProductType==VER_NT_WORKSTATION)						
					{
						m_bWin10 = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin10orLater=m_bWin2016orLater= m_bWin8orLater=m_bWin2012orLater= m_bWin8_1orLater=m_bWin2012R2orLater =true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows 10");
						wcscpy(	m_szOperatingSystemShortName,L"10");
					}
					else
					{
						m_bWin2016  = m_bWin2000orLater = m_bWinXPorLater = m_bWin2003orLater = m_bWinVistaorLater =m_bWin2008orLater = m_bWin2008R2orLater =m_bWin7orLater = true;
						m_bWin10orLater=m_bWin2016orLater= m_bWin8orLater=m_bWin2012orLater= m_bWin8_1orLater=m_bWin2012R2orLater =true;
						wcscpy(	m_szOperatingSystemName,L"Microsoft Windows Server 2016");
						wcscpy(	m_szOperatingSystemShortName,L"2016");
					}
				}
				break;
			}
		} // End Switch
	}
}

bool OS_Version::IsWin2000(void)
{
	return m_bWin2000;
}

bool OS_Version::IsWin2000orLater(void)
{
	return m_bWin2000orLater;
}

bool OS_Version::IsWinXP(void)
{
	return m_bWinXP;
}

bool OS_Version::IsWinXPorLater(void)
{
	return m_bWinXPorLater;
}

bool OS_Version::IsWin2003(void)
{
	 return m_bWin2003;
}

bool OS_Version::IsWin2003orLater(void)
{
	return m_bWin2003orLater;
}

bool OS_Version::IsWinVista(void)
{
	return m_bWinVista;
}

bool OS_Version::IsWinVistaorLater(void)
{
	return m_bWinVistaorLater;
}

bool OS_Version::IsWin2008(void)
{
	return m_bWin2008;
}

bool OS_Version::IsWin2008orLater(void)
{
	return m_bWin2008orLater;
}

bool OS_Version::IsWin7(void)
{
	return m_bWin7;
}

bool OS_Version::IsWin7orLater(void)
{
	return m_bWin7orLater;
}

bool OS_Version::IsWin2008r2(void)
{
	return m_bWin2008R2;
}

bool OS_Version::IsWin2008r2orLater(void)
{
	return m_bWin2008R2orLater;
}

bool OS_Version::IsWin8(void)
{
	return m_bWin8;
}

bool OS_Version::IsWin8orLater(void)
{
	return m_bWin8orLater;
}

bool OS_Version::IsWin2012(void)
{
	return m_bWin2012;
}

bool OS_Version::IsWin2012orLater(void)
{
	return m_bWin2012orLater;
}

bool OS_Version::IsWin8_1(void)
{
	return m_bWin8_1;
}

bool OS_Version::IsWin8_1orLater(void)
{
	return m_bWin8_1orLater;
}

bool OS_Version::IsWin2012r2(void)
{
	return m_bWin2012R2;
}

bool OS_Version::IsWin2012r2orLater(void)
{
	return m_bWin2012R2orLater;
}

bool OS_Version::IsWin10(void)
{
	return m_bWin10;
}

bool OS_Version::IsWin10orLater(void)
{
	return m_bWin10orLater;
}

bool OS_Version::IsWin2016(void)
{
	return m_bWin2016;
}

bool OS_Version::IsWin2016orLater(void)
{
	return m_bWin2016orLater;
}

bool OS_Version::IsWindowsServer()
{
	if (OSvi.dwMajorVersion<=5 && OSvi.dwMinorVersion<=1)
		return false;
	if (OSvi.wProductType!= VER_NT_WORKSTATION || OSvi.wSuiteMask & VER_SUITE_WH_SERVER)
		return true;
	else
		return false;
}

bool OS_Version::IsWindows64bit()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
		return true;
	else
		return false;
}

DWORD OS_Version::BuildNumber(void)
{
	 return m_dwBuildNumber;
}

const	LPWSTR OS_Version::CSD(void)
{
	 return m_szCSDVersion;
}

const	LPWSTR OS_Version::OperatingSystemName(void)
{
	return m_szOperatingSystemName;
}

const	LPWSTR OS_Version::OperatingSystemShortName(void)
{
	return m_szOperatingSystemShortName;
}
