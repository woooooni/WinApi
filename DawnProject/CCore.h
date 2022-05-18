#include "pch.h"

class CCore 
{
public:
	SINGLE(CCore);

private:
	HWND	m_hWnd = NULL;			// 메인 윈도우 핸들
	POINT	m_ptResolution = {};	// 메인 윈도우 해상도
	HDC		m_hDC;					// 메인 윈도우에 Draw할 DC

	HBITMAP	m_hBit;
	HDC m_memDC;
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd();
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
