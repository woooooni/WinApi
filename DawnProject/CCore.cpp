#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "resource.h"

CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
	
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++) {
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_ptResolutionVec = Vec2((float)_ptResolution.x, (float)_ptResolution.y);
	
	//해상도에 맞게 윈도우 크기를 조절.
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);
	
	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_DAWNPROJECT));
	m_hDC = GetDC(m_hWnd);

	//이중 버퍼링 용도의 비트맵과 DC를 만듦.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", 
													(UINT)m_ptResolution.x, 
													(UINT)m_ptResolution.y);

	//자주 사용할 브러쉬 및 펜 설정
	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCamera::GetInst()->Init();

	return S_OK;
}


void CCore::progress()
{
	// TODO : LOOP

	//Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();



	//===========
	//Scene Update
	//===========
	CSceneMgr::GetInst()->update();

	//충돌체크
	CCollisionMgr::GetInst()->update();

	//UI 이벤트 체크
	CUIMgr::GetInst()->update();


	//===========
	//Rendering
	//===========

	//화면 Clear
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	//===========
	//Event Update
	//===========
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);


	//red pen
	//green pen
	//blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255,0,0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));;
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResoultionVec(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResoultionVec(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}





