// stdafx.cpp : 只包括标准包含文件的源文件
// DialHelper.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

TCHAR gchMain[] = _T("Main");
TCHAR gchEntryName[] = _T("EntryName");
TCHAR gchUserCount[] = _T("UserCount");
TCHAR gchCurrentUser[] = _T("CurrentUser");
TCHAR gchLastUsername[] = _T("");
TCHAR gchLastTimeC[] = _T("LastTimeC");
TCHAR gchDialOnStart[] = _T("DialOnStart");
TCHAR gchAutoReDial[] = _T("AutoReDial");
TCHAR gchTimeout[] = _T("Timeout");
TCHAR gchMinimizedOnStart[] = _T("MinimizedOnStart");
TCHAR gchMinimizeOnConnect[] = _T("MinimizeOnConnect");
TCHAR gchHangUpOnExit[] = _T("HangUpOnExit");
TCHAR gchTimingDial[] = _T("TimeingDial");
TCHAR gchDialTime[] = _T("DialTime");
TCHAR gchEnableLog[] = _T("EnableLog");
TCHAR gchLogFile[] = _T("LogFile");

TCHAR gchUserName[] = _T("UserName");
TCHAR gchPassword[] = _T("Password");



CString L2S(LONG l)
{
	CString sss;
	wsprintf(sss.GetBuffer(512), _T("%ld"), l);
	sss.ReleaseBuffer();
	return sss;
}

CString D2S_2(double d)
{
	CString sss;
	wsprintf(sss.GetBuffer(512), _T("%.2f"), d);
	sss.ReleaseBuffer();
	return sss;
}

// void PrintError()
// {
// 	DWORD dw = GetLastError();
// 	LPVOID lpMsgBuf;
// 	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
// 		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
// 		dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language(LPTSTR) &lpMsgBuf,	0, NULL);// Process any inserts in lpMsgBuf.
// 	// Display the string.
// 	MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error",
// 		MB_OK | MB_ICONINFORMATION);
// 	// Free the buffer.
// 	LocalFree(lpMsgBuf);
// }
