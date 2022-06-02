#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 _vecPos = GetPos();
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		_vecPos.y -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		_vecPos.x -= 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		_vecPos.y += 200.f * DeltaTimef;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		_vecPos.x += 200.f * DeltaTimef;
	}
}

void CPlayer::render(HDC _dc)
{
	Vec2 _vecScale = GetScale();
	Vec2 _vecPos = GetPos();
	Rectangle(_dc,
		(int)_vecPos.x - _vecScale.x / 2,
		(int)_vecPos.y - _vecScale.y / 2,
		(int)_vecPos.x + _vecScale.x / 2,
		(int)_vecPos.y + _vecScale.y / 2);
}
