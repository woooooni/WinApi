#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_memDC(0)
	, m_hBit(0)
{
	
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	
	//�ػ󵵿� �°� ������ ũ�⸦ ����.
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}


void CCore::progress()
{
	// TODO : LOOP

	//Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();




	update();
	render();
}

void CCore::update()
{
	
	Vec2 vPos = g_obj.GetPos();


	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
		//TODO
		vPos.x -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
		//TODO
		vPos.x += 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD) {
		//TODO
		vPos.y -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD) {
		//TODO
		vPos.y += 200.f * DeltaTimef;
	}
	g_obj.SetPos(vPos);
	
}

void CCore::render()
{
	// TODO : ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	// TODO : �׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC,
		vPos.x - vScale.x / 2.f,
		vPos.y - vScale.y / 2.f,
		vPos.x + vScale.x / 2.f,
		vPos.y + vScale.y / 2.f);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, 
			m_memDC, 0, 0, SRCCOPY);
}

HWND CCore::GetMainHwnd()
{
	return m_hWnd;
}

