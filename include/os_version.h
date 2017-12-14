#ifndef __WINDOWS_VERSION_H
#define __WINDOWS_VERSION_H
#pragma once

class OS_Version
{
public:
	// Functions
	OS_Version();													// Constructor
	bool	IsWin2000(void);
	bool	IsWin2000orLater(void);
	bool	IsWinXP(void);											// Returns true if WinXP
	bool	IsWinXPorLater(void);									// Returns true if WinXP+
	bool	IsWin2003(void);										// Returns true if Win2003 Server
	bool	IsWin2003orLater(void);									// Returns true if Win2003+
	bool	IsWinVista(void);										// Returns true if WinVista
	bool	IsWinVistaorLater(void);								// Returns true if WinVista+
	bool	IsWin2008(void);										// Returns true if Win2008 Server
	bool	IsWin2008orLater(void);									// Returns true if Win2008+
	bool	IsWin7(void);											// Returns true if Win7
	bool	IsWin7orLater(void);									// Returns true if Win7+
	bool	IsWin2008r2(void);										// Returns true if Win2008 R2 Server
	bool	IsWin2008r2orLater(void);								// Returns true if Win2008 R2 +
	bool	IsWin8(void);											// Returns true if Win8
	bool	IsWin8orLater(void);									// Returns true if Win8+
	bool	IsWin2012(void);										// Returns true if Win2012 Server
	bool	IsWin2012orLater(void);									// Returns true if Win2012+
	bool	IsWin8_1(void);											// Returns true if Win8.1
	bool	IsWin8_1orLater(void);									// Returns true if Win8.1+
	bool	IsWin2012r2(void);										// Returns true if Win2012 R2 Server
	bool	IsWin2012r2orLater(void);								// Returns true if Win2012 R2 +
	bool	IsWin10(void);											// Returns true if Win10
	bool	IsWin10orLater(void);									// Returns true if Win10+
	bool	IsWin2016(void);										// Returns true if Win2016 Server
	bool	IsWin2016orLater(void);									// Returns true if Win2016+

	bool	IsWindowsServer();
	bool	IsWindows64bit();

	DWORD	BuildNumber(void);
	const	LPWSTR CSD(void);										// Returns Service Pack
	const	LPWSTR OperatingSystemName(void);						// Returns Operating System Name
	const	LPWSTR OperatingSystemShortName(void);					// Returns Operating System Name
	OSVERSIONINFOEXW OSvi;
private:

	// Variables
	DWORD			m_dwMajorVersion;								// Major OS version
	DWORD			m_dwMinorVersion;								// Minor OS version
	DWORD			m_dwBuildNumber;								// Build number
	WCHAR			m_szCSDVersion [256];
	WCHAR			m_szOperatingSystemName[256];
	WCHAR			m_szOperatingSystemShortName[256];
	bool			m_bWin2000;
	bool			m_bWin2000orLater;
	bool			m_bWinXP;
	bool			m_bWinXPorLater;
	bool			m_bWin2003;
	bool			m_bWin2003orLater;
	bool			m_bWinVista;
	bool			m_bWinVistaorLater;
	bool			m_bWin2008;
	bool			m_bWin2008orLater;
	bool			m_bWin7;
	bool			m_bWin7orLater;
	bool			m_bWin2008R2;
	bool			m_bWin2008R2orLater;
	bool			m_bWin8;
	bool			m_bWin8orLater;
	bool			m_bWin2012;
	bool			m_bWin2012orLater;
	bool			m_bWin8_1;
	bool			m_bWin8_1orLater;
	bool			m_bWin2012R2;
	bool			m_bWin2012R2orLater;
	bool			m_bWin10;
	bool			m_bWin10orLater;
	bool			m_bWin2016;
	bool			m_bWin2016orLater;
};

///////////////////////////////////////////////////////////////////////////////

#endif

