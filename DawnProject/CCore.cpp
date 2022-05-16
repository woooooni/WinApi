#include "pch.h"
#include "CCore.h"

CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	
{
	
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	
	//해상도에 맞게 윈도우 크기를 조절.
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	return S_OK;
}

void CCore::progress()
{
	// TODO : LOOP

	
}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC);
}