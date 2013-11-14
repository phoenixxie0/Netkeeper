// DialHelper.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "DialHelper.h"
#include "DialHelperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialHelperApp

BEGIN_MESSAGE_MAP(CDialHelperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDialHelperApp 构造

CDialHelperApp::CDialHelperApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CDialHelperApp 对象

CDialHelperApp theApp;


// CDialHelperApp 初始化

BOOL CDialHelperApp::InitInstance()
{
	AfxOleInit();
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//从此开始为限制程序多开------------
	CWnd* pWndPrev;
	CWnd* pWndChild;
	//查找窗体
	pWndPrev = CWnd::FindWindow(_T("#32770"), CAPTION_NAME);
	if (pWndPrev)
	{
		pWndChild = pWndPrev->GetLastActivePopup();

		if (pWndPrev->IsIconic())
			pWndPrev->ShowWindow(SW_RESTORE);
		pWndChild->SetForegroundWindow();
		return FALSE;
	}
	//此为限制程序多开-的结束部分-----------
	//获取命令行参数
	CString aaa = m_lpCmdLine;
	aaa.MakeUpper();
	if (aaa.Find(_T("/AUTO")) != -1)
	{
		bAUTO = TRUE;
	}
	else
	{
		bAUTO = FALSE;
	}

	//获得完整的路径和文件名
	GetModuleFileName(NULL, sExePath.GetBuffer(MAX_PATH), MAX_PATH);
	//释放空间
	sExePath.ReleaseBuffer();

	sExePath.MakeReverse();
	sExePath = sExePath.Right(sExePath.GetLength() - sExePath.Find(_T('\\')));
	sExePath.MakeReverse();
	// 	TRACE(sIniFileName);
	// 	TRACE("\n");
	sIniFileName = sExePath + _T("NetKeeper.ini");
	sLogFileName = sExePath + _T("NetKeeper.log");

	pDlg = new CDialHelperDlg;
	m_pMainWnd = pDlg;
	INT_PTR nResponse = pDlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

CString CDialHelperApp::GetIniString(CString sec, CString key, CString str)
{
	CString sss;
	GetPrivateProfileString(sec, key, str, sss.GetBuffer(512), 511,
		sIniFileName);
	sss.ReleaseBuffer();
	return sss;
}

BOOL CDialHelperApp::SetIniString(CString sec, CString key, CString str)
{
	return WritePrivateProfileString(sec, key, str, sIniFileName);
}
// BOOL CDialHelperApp::LOG(UINT nID)
// {
// 	CString sss;
// 	if (!sss.LoadString(nID)) return FALSE;
// 	LOG(sss);
// 	return TRUE;
// }
// BOOL CDialHelperApp::LOG(CString sss)
// {
// 	TRY
// 	{
// 		CFile f(sLogFileName,
// 			CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone);
// 		TRY
// 		{
// 			//到文件的最后
// 			f.SeekToEnd();
// 			//得到当前的时间
// 			CTime t = CTime::GetCurrentTime();
// 			CString aaa;
// 			//按照一定的日期格式输出
// 			wsprintf(aaa.GetBuffer(512),
// 				_T("%4d-%02d-%02d %02d:%02d:%02d %s\r\n"),
// 				t.GetYear(), t.GetMonth(), t.GetDay(),
// 				t.GetHour(), t.GetMinute(), t.GetSecond(), sss);
// 			aaa.ReleaseBuffer();
// 			f.Write(aaa, aaa.GetLength());
// 			f.Close();
// 		}
// 		CATCH(CFileException, e)
// 		{
// 			//关闭文件
// 			f.Close();
// 		}
// 		END_CATCH
// 	}
// 	CATCH(CFileException, e)
// 	{
// 		TRACE(CString(_T("文件不能被打开") + e->m_cause) + _T("\n"));
// 		return FALSE;
// 	}
// 	END_CATCH
// 		return TRUE;
// }

VOID CDialHelperApp::PostDialMessage(UINT unMsg, WPARAM rasconnstate,
	DWORD dwError)
{
	pDlg->PostMessage(WM_DIAL_FUNC, rasconnstate, dwError);
}
