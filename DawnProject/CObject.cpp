#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	:m_vPos{}
	, m_vScale{}
{
	
}

CObject::~CObject()
{
		
}

void CObject::update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD) 
	{
		m_vPos.y -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		m_vPos.x -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		m_vPos.y += 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		m_vPos.x += 200.f * DeltaTimef;
	}
}

void CObject::render(HDC _dc)
{

	Rectangle(_dc,
		(int)m_vPos.x - m_vScale.x / 2,
		(int)m_vPos.y - m_vScale.y / 2,
		(int)m_vPos.x + m_vScale.x / 2,
		(int)m_vPos.y + m_vScale.y / 2);
}


void CObject::SetPos(Vec2 _vPos)
{
	m_vPos = _vPos;
}

void CObject::SetScale(Vec2 _vScale)
{
	m_vScale = _vScale;
}

Vec2 CObject::GetPos()
{
	return m_vPos;
}

Vec2 CObject::GetScale()
{
	return m_vScale;
}

