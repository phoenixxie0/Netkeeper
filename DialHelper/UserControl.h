#pragma once
#include "afxcmn.h"


// CUserControl 对话框

class CUserControl : public CDialog
{
	DECLARE_DYNAMIC(CUserControl)

public:
	CUserControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserControl();


	virtual void OnFinalRelease();

	// 对话框数据
	enum
	{
		IDD = IDD_DIALOG_USERCONTROL
	};
protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CListCtrl CLC_UserInfo;
	BOOL ReloadUserInfo();
	BOOL InitUserInfo();
public:
	afx_msg void OnBnClickedButtonNew();
public:
	afx_msg void OnBnClickedButtonChange();
public:
	afx_msg void OnBnClickedButtonDelete();
};
