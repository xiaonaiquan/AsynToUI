#pragma once

namespace Module
{
	class BEvent_Impl;
	class UIEventManager final
	{
	public:

		UIEventManager();

		~UIEventManager();

	public:
		int          startup();
		void         shutdown();
		int          asynFireUIEvent(const BEvent_Impl* const pEvent);

	private:
		BOOL _registerClass();
		void _removeEvents();
		void _processEvent(BEvent_Impl* pEvent, BOOL bRelease);
		static LRESULT _stdcall _WindowProc(HWND hWnd
			, UINT message
			, WPARAM wparam
			, LPARAM lparam);
	private:
		UIEventManager& operator=(UIEventManager&);
		UIEventManager(const UIEventManager&);
	private:
		HWND m_hWnd;

	};


	UIEventManager* getEventManager();
}