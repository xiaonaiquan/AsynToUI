#include "stdafx.h"
#include "MainDlg.h"
#include "MainModule.h"
#include <thread>

CMainDlg::CMainDlg(LPCTSTR pszXMLPath) :m_strXMLPath(pszXMLPath)
{

}

CMainDlg::~CMainDlg()
{
	Module::getMainModule()->removeObserver(this);
}

CDuiString CMainDlg::GetSkinFile()
{
	return m_strXMLPath;
}

LPCTSTR CMainDlg::GetWindowClassName(void) const
{
	return _T("MainWnd");
}

void CMainDlg::InitWindow()
{
	Module::getMainModule()->addObserver(this, std::bind(&CMainDlg::TestCallBack, this, std::placeholders::_1, std::placeholders::_2));
}

void CMainDlg::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender->GetName() == _T("send"))
		{
			//MessageBox(NULL, L"ss", L"sss", NULL);
			std::thread t([](){
				std::string str = "test";
				Module::getMainModule()->asynNotifyObserver("a", str);
			});
			t.detach();
		}
		else if (msg.pSender->GetName() == _T("btn_close"))
		{
			Close(0);
		}
	}
}

void CMainDlg::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

std::wstring StringtoWString(const std::string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

void CMainDlg::TestCallBack(const std::string& keyId, B_TUPLE_PARAM bParam)
{
	if (keyId.compare("a") == 0)
	{
		std::string data = std::get<0>(bParam);
		MessageBox(NULL, StringtoWString(data).c_str(), L"·µ»ØÖµ", NULL);
	}
}