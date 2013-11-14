// UserControl.cpp : 实现文件
//

#include "stdafx.h"
#include "DialHelper.h"
#include "UserControl.h"
#include "CreatUserInfo.h"


// CUserControl 对话框

IMPLEMENT_DYNAMIC(CUserControl, CDialog)

CUserControl::CUserControl(CWnd* pParent /*=NULL*/) : CDialog(CUserControl::IDD, pParent)
{
	EnableAutomation();
}

CUserControl::~CUserControl()
{
}

void CUserControl::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CDialog::OnFinalRelease();
}

void CUserControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, CLC_UserInfo);
}

BOOL CUserControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUserInfo();
	ReloadUserInfo();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CUserControl, CDialog)
	ON_BN_CLICKED(ID_BUTTON_NEW, &CUserControl::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CUserControl::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CUserControl::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CUserControl, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IUserControl 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {21490940-CCD4-4738-B553-87D2DDE3D370}
static const IID IID_IUserControl =
{
	0x21490940, 0xCCD4, 0x4738,
	{ 0xB5, 0x53, 0x87, 0xD2, 0xDD, 0xE3, 0xD3, 0x70 }
};

BEGIN_INTERFACE_MAP(CUserControl, CDialog)
INTERFACE_PART(CUserControl, IID_IUserControl, Dispatch)
END_INTERFACE_MAP()

BOOL CUserControl::ReloadUserInfo()
{
	CLC_UserInfo.DeleteAllItems();
	for (int i = 1; i <= theApp.pDlg->m_iUserCount; i++)
	{
		CLC_UserInfo.InsertItem(i - 1, L2S(i));
		CLC_UserInfo.SetItemText(i - 1, 1, theApp.pDlg->GetUserName(i));
		CLC_UserInfo.SetItemText(i - 1, 2, theApp.pDlg->GetPassword(i));
	}
	UpdateData();
	return TRUE;
}

BOOL CUserControl::InitUserInfo()
{
	CLC_UserInfo.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 40);
	CLC_UserInfo.InsertColumn(1, _T("用户名"), LVCFMT_LEFT, 150);
	CLC_UserInfo.InsertColumn(2, _T("密码"), LVCFMT_LEFT, 120);
	CLC_UserInfo.SetExtendedStyle(CLC_UserInfo.GetExtendedStyle() |
					LVS_EX_FULLROWSELECT) ;
	return TRUE;
}
// CUserControl 消息处理程序

void CUserControl::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CCreatUserInfo* cui = new CCreatUserInfo(theApp.pDlg->m_iUserCount + 1,
								NULL);
	cui->DoModal();
	ReloadUserInfo();
}

void CUserControl::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	if (CLC_UserInfo.GetSelectionMark() == -1)
	{
		MessageBox(_T("请选择要修改的项！"), _T("提示"));
	}
	else
	{
		CCreatUserInfo* cui = new CCreatUserInfo(CLC_UserInfo.GetSelectionMark() +
									1);
		cui->DoModal();
		ReloadUserInfo();
	}
}

void CUserControl::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (CLC_UserInfo.GetSelectionMark() == -1)
	{
		MessageBox(_T("请选择要删除的项！"), _T("提示"));
	}
	else
	{
		for (INT i = CLC_UserInfo.GetSelectionMark() + 1;
			i < theApp.pDlg->m_iUserCount;
			i++)
		{
			theApp.pDlg->SaveUserInfo(i, theApp.pDlg->GetUserName(i + 1),
							theApp.pDlg->GetPassword(i + 1));
		}

		CString sss = _T("User") + L2S(theApp.pDlg->m_iUserCount);
		theApp.SetIniString(sss, gchUserName, NULL);
		theApp.SetIniString(sss, gchPassword, NULL);
		//边界判定，m_iUserCount必须大于等于1
		if (theApp.pDlg->m_iUserCount > 1)
		{
			(theApp.pDlg->m_iUserCount)--;
		}
		//边界判定，m_iCurrentUser必须小于等于m_iUserCount
		if (theApp.pDlg->m_iCurrentUser > theApp.pDlg->m_iUserCount)
		{
			theApp.pDlg->m_iCurrentUser = theApp.pDlg->m_iUserCount;
		}

		theApp.pDlg->SaveAllToIni();
		ReloadUserInfo();
	}
}
