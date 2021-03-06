#pragma once
#include "pch.h"
class CTexture;
class CCore 
{
public:
	SINGLE(CCore);

private:
	HWND		m_hWnd = NULL;			// 메인 윈도우 핸들
	POINT		m_ptResolution = {};	// 메인 윈도우 해상도
	Vec2		m_ptResolutionVec = {};
	HDC			m_hDC;					// 메인 윈도우에 Draw할 DC

	CTexture*	m_pMemTex;				// 백버퍼 텍스쳐

	//자주 사용할 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	//메뉴
	HMENU	m_hMenu;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDc() { return m_hDC; };

	POINT GetResoultion() { return m_ptResolution; }
	Vec2 GetResoultionVec() { return Vec2((float)m_ptResolution.x, (float)m_ptResolution.y); }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; };
};

//#pragma once
//
//// 싱글톤 패턴
//// 객체의 생성을 1개로 제한.
//class CCore
//{
//private:
//	static CCore* Instance;
//public:
//	static CCore* GetInstance() 
//	{
//		if (Instance == nullptr) 
//		{
//			Instance = new CCore;
//		}
//		return Instance;
//	}
//
//	static void Release() 
//	{
//		if (nullptr != Instance)
//		{
//			delete Instance;
//			Instance = nullptr;
//		}
//	}
//	
//private:
//	CCore();
//	~CCore();
//};
//
