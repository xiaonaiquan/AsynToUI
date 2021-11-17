// AsynToUI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "AsynToUI.h"
#include "MainDlg.h"
#include "UIEventManager.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。

	Module::getEventManager()->startup();

	CPaintManagerUI::SetInstance(hInstance);// 加载XML的时候，需要使用该句柄去定位EXE的路径，才能加载XML的路径

	CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourcePath(L"skin");
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	CMainDlg wnd(_T("MainDlg.xml"));
	wnd.Create(NULL, _T("Demo"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	wnd.CenterWindow();
	wnd.ShowWindow();

	CPaintManagerUI::MessageLoop();

	Module::getEventManager()->shutdown();

	::CoUninitialize();
	return 0;
}