// DialHelper.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "DialHelperDlg.h"

#define  CAPTION_NAME _T("星空助手 V1.3 喵喵喵")



// CDialHelperApp:
// 有关此类的实现，请参阅 DialHelper.cpp
//

class CDialHelperApp : public CWinApp
{
public:
	CDialHelperApp();
	CDialHelperDlg* pDlg;
	CString sExePath;
	CString sLogFileName;
	CString sIniFileName;
	CString GetIniString(CString sec, CString key, CString str);
	BOOL SetIniString(CString sec, CString key, CString str);

	BOOL bAUTO;
	// 	BOOL LOG(UINT nID);
	// 	BOOL LOG(CString sss);

	VOID PostDialMessage(UINT unMsg, WPARAM rasconnstate, DWORD dwError);

	// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
};

extern CDialHelperApp theApp;