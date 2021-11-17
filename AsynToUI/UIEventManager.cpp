#include "stdafx.h"
#include "UIEventManager.h"
#include "ModuleObserverP.h"

namespace Module
{
	static const wchar_t uiEventWndClass[] = L"uiEventManager_class";
	#define UI_EVENT_MSG				WM_USER + 1005


	UIEventManager::UIEventManager() : m_hWnd(NULL)
	{

	}

	UIEventManager::~UIEventManager()
	{
		try
		{
			shutdown();
		}
		catch (...)
		{
			assert(FALSE);
		}
	}

	BOOL UIEventManager::_registerClass()
	{
		WNDCLASSEXW wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = _WindowProc;
		wc.hInstance = ::GetModuleHandle(0);
		wc.lpszClassName = uiEventWndClass;
		ATOM ret = ::RegisterClassExW(&wc);
		ASSERT(ret != NULL);
		if (NULL == ret || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS)
			return FALSE;

		return TRUE;
	}


	int UIEventManager::startup()
	{
		int errCode = 0;

		if (0 != m_hWnd)
			return 0;
		else
		{
			if (!_registerClass())
				return -1;
			m_hWnd = ::CreateWindowW(uiEventWndClass, _T("uiEvnetManager_window"),
				0, 0, 0, 0, 0, HWND_MESSAGE, 0, GetModuleHandle(0), 0);
		}

		if (FALSE == ::IsWindow(m_hWnd))
			errCode = -1;

		return errCode;
	}

	void UIEventManager::shutdown()
	{
		if (NULL != m_hWnd)
		{
			::DestroyWindow(m_hWnd);
			::UnregisterClassW(uiEventWndClass, ::GetModuleHandle(NULL));
			m_hWnd = NULL;
		}
	}

	LRESULT _stdcall UIEventManager::_WindowProc(HWND hWnd
		, UINT message
		, WPARAM wparam
		, LPARAM lparam)
	{
		switch (message)
		{
		case UI_EVENT_MSG:
		{
			reinterpret_cast<UIEventManager*>(wparam)->_processEvent(reinterpret_cast<BEvent_Impl*>(lparam), TRUE);
			break;
		}

		default:
			break;
		}
		return ::DefWindowProc(hWnd, message, wparam, lparam);
	}

	void UIEventManager::_processEvent(BEvent_Impl* pEvent, BOOL bRelease)
	{
		assert(pEvent);
		if (nullptr == pEvent)
		{
			return;
		}
		pEvent->process();

		if (bRelease)
		{
			pEvent->release();
		}
	}

	int UIEventManager::asynFireUIEvent(const BEvent_Impl* const pEvent)
	{
		assert(m_hWnd);
		assert(pEvent);
		if (0 == m_hWnd || 0 == pEvent)
			return -1;

		if (FALSE == ::PostMessage(m_hWnd, UI_EVENT_MSG, reinterpret_cast<WPARAM>(this), reinterpret_cast<WPARAM>(pEvent)))
			return -1;

		return 0;
	}

	Module::UIEventManager* getEventManager()
	{
		static UIEventManager manager;
		return &manager;
	}
}