#pragma once


// CCreatUserInfo 对话框

class CCreatUserInfo : public CDialog
{
	DECLARE_DYNAMIC(CCreatUserInfo)

public:
	// 	CCreatUserInfo(CWnd* pParent = NULL);   // 标准构造函数
	CCreatUserInfo(INT i, CWnd* pParent = NULL) ;
	virtual ~CCreatUserInfo();

	virtual void OnFinalRelease();

	// 对话框数据
	enum
	{
		IDD = IDD_DIALOG_NEWUSER
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_sUserName;
	CString m_sPassword;
	INT m_iCurrentUser;
public:
	afx_msg void OnBnClickedOk();
};
