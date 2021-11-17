#pragma once
#include "ModuleDefine.h"

class CMainDlg : public WindowImplBase
{
public:
	explicit CMainDlg(LPCTSTR pszXMLPath);
	~CMainDlg();


public:
	void TestCallBack(const std::string& keyId, B_TUPLE_PARAM bParam);
protected:
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);

	virtual void OnFinalMessage(HWND hWnd);
private:
	CDuiString m_strXMLPath;

	CButtonUI *m_pSendUI;
};