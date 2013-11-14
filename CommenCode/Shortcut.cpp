


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#include "Shortcut.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 宏定义
#define STR_QuickLaunch		TEXT("\\Microsoft\\Internet Explorer\\Quick Launch")	// 快速启动路径
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取特殊文件夹路径
BOOL CShortcut::GetFolder(INT iFolder, PTSTR ptzFolder)
{
	BOOL bResult;
	LPMALLOC pMalloc;
	LPITEMIDLIST pIdl;

	bResult = FALSE;
	if (SHGetMalloc(&pMalloc) == S_OK)
	{
		if (SHGetSpecialFolderLocation(NULL, iFolder, &pIdl) == S_OK)
		{
			bResult = SHGetPathFromIDList(pIdl, ptzFolder);
			pMalloc->Free(pIdl);
		}
		pMalloc->Release();
	}
	return bResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 判断快捷方式是否存在
BOOL CShortcut::Exist(INT iFolder, PCTSTR ptzName)
{
	PTSTR ptzFileName;
	TCHAR tzPath[MAX_PATH];
	TCHAR tzBuffer[MAX_PATH];

	if (GetFolder(iFolder, tzPath) == FALSE)
	{
		return FALSE;
	}

	if (iFolder == CSIDL_APPDATA)
	{
		lstrcat(tzPath, STR_QuickLaunch);
	}

	return SearchPath(tzPath, ptzName, NULL, MAX_PATH, tzBuffer, &ptzFileName);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建快捷方式
BOOL CShortcut::Create(INT iFolder, PCTSTR ptzName, PCTSTR ptzDesc)
{
	HRESULT hResult;
	TCHAR tzPath[MAX_PATH];
	WCHAR wzPath[MAX_PATH];
	IShellLink* pShellLink;
	IPersistFile* pPersistFile;

	if (GetFolder(iFolder, tzPath) == FALSE)
	{
		return FALSE;
	}
	if (iFolder == CSIDL_APPDATA)
	{
		lstrcat(tzPath, STR_QuickLaunch);
	}
	lstrcat(tzPath, TEXT("\\"));
	lstrcat(tzPath, ptzName);

#ifdef UNICODE
	lstrcpy(wzPath, tzPath);
#else // UNICODE
	MultiByteToWideChar(CP_ACP, 0, tzPath, -1, wzPath, MAX_PATH);
#endif // UNICODE

	hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
				IID_IShellLink, (PVOID *) &pShellLink);
	if (hResult == S_OK)
	{
		hResult = pShellLink->QueryInterface(IID_IPersistFile,
								(PVOID *) &pPersistFile);
		if (hResult == S_OK)
		{
			GetModuleFileName(NULL, tzPath, MAX_PATH);
			hResult = pShellLink->SetPath(tzPath);
			if (hResult == S_OK)
			{
				if (ptzDesc)
				{
					pShellLink->SetDescription(ptzDesc);
				}
				hResult = pPersistFile->Save(wzPath, FALSE);
			}
			pPersistFile->Release();
		}
		pShellLink->Release();
	}

	return (hResult == S_OK);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 删除快捷方式
BOOL CShortcut::Remove(INT iFolder, PCTSTR ptzName)
{
	TCHAR tzPath[MAX_PATH];

	if (GetFolder(iFolder, tzPath) == FALSE)
	{
		return FALSE;
	}

	if (iFolder == CSIDL_APPDATA)
	{
		lstrcat(tzPath, STR_QuickLaunch);
	}
	lstrcat(tzPath, TEXT("\\"));
	lstrcat(tzPath, ptzName);

	return DeleteFile(tzPath);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
