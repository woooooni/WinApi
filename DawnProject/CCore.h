#include "pch.h"

class CCore 
{
public:
	SINGLE(CCore);

private:
	HWND	m_hWnd = NULL;			// ���� ������ �ڵ�
	POINT	m_ptResolution = {};	// ���� ������ �ػ�
	HDC		m_hDC;					// ���� �����쿡 Draw�� DC

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
