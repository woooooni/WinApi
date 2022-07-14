#pragma once
#include "pch.h"
class CTexture;
class CCore 
{
public:
	SINGLE(CCore);

private:
	HWND		m_hWnd = NULL;			// ���� ������ �ڵ�
	POINT		m_ptResolution = {};	// ���� ������ �ػ�
	Vec2		m_ptResolutionVec = {};
	HDC			m_hDC;					// ���� �����쿡 Draw�� DC

	CTexture*	m_pMemTex;				// ����� �ؽ���

	//���� ����� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	//�޴�
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
//// �̱��� ����
//// ��ü�� ������ 1���� ����.
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
