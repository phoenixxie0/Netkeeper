//////////////////////////////////////////////////////////////////////////
// 星空用户名生成头文件
// 作者:Phoenix
// 版本:1.3
//////////////////////////////////////////////////////////////////////////

#include <afx.h>
class CXKUsername
{
public:
	CXKUsername(CString username, INT ver = 32, long lasttimec = 0);
	CString Realusername();
	long GetLastTimeC();
private:
	INT m_ver;				//星空的版本，V12、V18、V29、V32
	long m_lasttimec;		//上次成功的时间处理
	CString m_username;		//原始用户名
	CString m_realusername;	//真正的用户名
	CString RADIUS;
	CString LR;
};
