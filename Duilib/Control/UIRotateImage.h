#ifndef RotateImageUI_h__
#define RotateImageUI_h__
#pragma once

namespace DuiLib
{
	class CControl;

#define EVENT_TIME_ID	100

	class UILIB_API CRotateImageUI : public CControlUI
	{
		DECLARE_DUICONTROL(CRotateImageUI)
	public:
		CRotateImageUI();
		~CRotateImageUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void	DoInit() override;
		void	DoEvent(TEventUI& event) override;
		void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
		void	SetVisible(bool bVisible = true) override;

		void SetPos(RECT rc, bool bNeedInvalidate = true);

		void	SetTimeInterval(const int& nValue);
		int		GetTimeInterval();
		void	SetEachTimeAngle(const int& nValue);
		int		GetEachTimeAngle();
		void	SetFixAngle(const int& nValue);
		int		GetFixAngle();
		void	SetBkImage(const CDuiString& strImage);
		void	SetStretch(const bool& bStretch);
		bool	GetStretch();
		void	SetAutoStart(const bool& bAutoStart);
		bool	GetAutoStart();
		void	Stop();
		void	Start();
		void	Pause();

		void	PaintBkImage(HDC hDC);

	protected:
		Gdiplus::Image*	LoadImg(LPCTSTR pstrImgPath);
		void	InitInfo();

	protected:
		int m_nTimeInterval;			//ʱ����(���ٺ�����תһ��) ��λms
		int m_nAngle;					//ÿ����ת�Ƕ�
		bool m_bStretch;				//�Ƿ��Զ�����ͼƬ
		bool m_bIsAutoStart;			//�Ƿ��Զ���ʼ��ת
		int m_nFixAngle;				//�̶���ת�Ƕ�		

		int m_nCurAngle;
		Gdiplus::Image*	m_pBkimage;
		IStream* m_pStream;
		CDuiString m_sBkImage;
		bool m_bIsPlaying;				//�Ƿ�������ת

		Gdiplus::PointF m_centerPos;
	};
}

#endif // RotateImageUI_h__