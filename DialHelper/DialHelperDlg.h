// DialHelperDlg.h : 头文件
//

#pragma once
#pragma comment(lib, "Rasapi32.lib") 
#include <ras.h>
#include <raserror.h>
#include <RasDlg.h>
#include "afxcmn.h"
#include "afxwin.h"




// CDialHelperDlg 对话框
class CDialHelperDlg : public CDialog
{
	// 构造
public:
	CDialHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

	//自己定义的函数-------------------------------------------------------------------------------------

	BOOL bDialing;			//是否正在连接
	BOOL bDialNow;			//是否要拨号
	BOOL bConnected;		//是否已连接
	BOOL bInOnTimer;		//是否启用了定时器
	CTime tBeginDial;		//开始拨号时间 供定时器用
	UINT_PTR uTimer;		//定时器
	UINT_PTR uTimer2;
	BOOL bInOnTimer2;		//是否启用了定时器

//	CTrayIcon cti;

	RASENTRYNAME m_renEntries[20];
	ULONG m_ulEntryCount;

	BOOL SaveAllToIni();	//设置存储
	BOOL LoadAllFromIni();	//设置读取
	BOOL SaveLastTimeC();	//存储LastTimeC
	BOOL LoadCurrentUserInfo(INT i = 1);	//载入当前用户信息
	BOOL SaveUserInfo(INT i = 1, CString un = _T(""), CString pw = _T(""));	//保存当前用户信息
	BOOL LoadAllUserInfo();
	CString GetUserName(INT i);
	CString GetPassword(INT i);

	BOOL StartDial();
	BOOL HangUp(BOOL bExitApp);	//挂断

	BOOL QueryConnections(CString sEntryName = _T(""));
	CString GetRasConnState(RASCONNSTATE rasconn);
	BOOL CheckingConnected();
	BOOL CheckingDialing();
	BOOL CheckExternalConnect();
	BOOL GetActiveConnectionParam(CString& Conn, CString& Phon);


	void SetButtonsState();	//设置按钮状态
	//自己定义的函数-结束部分------------------------------------------------------------------------------------

	// 对话框数据
	enum
	{
		IDD = IDD_DialHelper_DIALOG
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CString m_sEntryName;
	CString m_sUserName;
	CString m_sPassword;

	INT m_iUserCount;
	INT m_iCurrentUser;
	LONG m_lLastTimeC;
	BOOL m_bDialOnStart;
	BOOL m_bAutoReDial;
	INT m_iTimeout;
	BOOL m_bMinimizedOnStart;
	BOOL m_bMinimizedOnConnect;
	BOOL m_bHangUpOnExit;
// 	BOOL m_bEnableLog;
// 	CString m_sLogFile;
	


	CString m_StatusText;

public:
	afx_msg void OnBnClickedCheckAutodial();
	afx_msg void OnBnClickedCheckRedial();
	afx_msg void OnBnClickedCheckOnlineMinsize();
	afx_msg void OnBnClickedCheckHangup();
	afx_msg void OnBnClickedCheckLog();
	afx_msg void OnEnChangeEditRedialTime();
	afx_msg void OnBnClickedButtonOpenlog();
	afx_msg void OnEnChangeEditPassword();
	afx_msg void OnBnClickedButtonOption();
	afx_msg void OnBnClickedButtonProvEdit();
	afx_msg void OnDial();
	afx_msg LRESULT OnDialFunc(WPARAM w, LPARAM l);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	/*CProgressCtrl m_ProgressTimeout;*/
public:
	DWORD CreatEntry(CString sEntryName, CString sUserName = _T(""),
		CString sPassword = _T(""));
public:
	afx_msg void OnDestroy();
public:
	CComboBox CB_USERNAME;
public:
	afx_msg void OnCbnSelchangeCboUsername();

public:
	afx_msg void OnBnClickedButtonUsercontrol();
public:
	CString sText;
public:
	afx_msg void OnBnClickedHangup();
public:
	afx_msg void OnBnClickedButtonAbout();
public:
	CString sLastError;
public:
	afx_msg void OnBnClickedbtnautoshortcut();
public:
	BOOL bIsTimingDial;
public:
	afx_msg void OnBnClickedchktimeingdial();
public:
	afx_msg void OnDtnDatetimechangedtdialtime(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedbtnsaveini();
public:
	COleDateTime codtDialTime;
public:
	CString strDialTime;
public:
	afx_msg void OnBnClickedButton1();
};
