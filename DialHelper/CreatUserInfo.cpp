// CreatUserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DialHelper.h"
#include "CreatUserInfo.h"


// CCreatUserInfo 对话框

IMPLEMENT_DYNAMIC(CCreatUserInfo, CDialog)

// CCreatUserInfo::CCreatUserInfo(CWnd* pParent /*=NULL*/)
// : CDialog(CCreatUserInfo::IDD, pParent)
// , m_sUserName(_T(""))
// , m_sPassword(_T(""))
// {
// 	EnableAutomation();
// }
CCreatUserInfo::CCreatUserInfo(INT i, CWnd* pParent /*=NULL*/) : CDialog(CCreatUserInfo::IDD, pParent),
	m_sUserName(_T("")), m_sPassword(_T(""))
{
	m_iCurrentUser = i;
	EnableAutomation();
}

CCreatUserInfo::~CCreatUserInfo()
{
}

void CCreatUserInfo::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CDialog::OnFinalRelease();
}

void CCreatUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDV_MaxChars(pDX, m_sPassword, 20);
	DDV_MaxChars(pDX, m_sUserName, 20);
}

BOOL CCreatUserInfo::OnInitDialog()
{
	m_sUserName = theApp.pDlg->GetUserName(m_iCurrentUser);
	m_sPassword = theApp.pDlg->GetPassword(m_iCurrentUser);
	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CCreatUserInfo, CDialog)
	ON_BN_CLICKED(IDOK, &CCreatUserInfo::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCreatUserInfo, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ICreatUserInfo 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {A23F3EEB-7E27-4995-AF1F-3DFE8EF4FE65}
static const IID IID_ICreatUserInfo =
{
	0xA23F3EEB, 0x7E27, 0x4995,
	{ 0xAF, 0x1F, 0x3D, 0xFE, 0x8E, 0xF4, 0xFE, 0x65 }
};

BEGIN_INTERFACE_MAP(CCreatUserInfo, CDialog)
INTERFACE_PART(CCreatUserInfo, IID_ICreatUserInfo, Dispatch)
END_INTERFACE_MAP()


// CCreatUserInfo 消息处理程序

void CCreatUserInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_sUserName.IsEmpty() || m_sPassword.IsEmpty())
	{
		MessageBox(_T("请填写用户名和密码！"), _T("提示"));
	}
	else
	{
		if (m_iCurrentUser > theApp.pDlg->m_iUserCount)
		{
			(theApp.pDlg->m_iUserCount)++;
			theApp.pDlg->SaveAllToIni();
		} 
		theApp.pDlg->SaveUserInfo(m_iCurrentUser, m_sUserName, m_sPassword);
		OnOK();
	}
}
