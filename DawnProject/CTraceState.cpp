#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CTraceState.h"


CTraceState::CTraceState()
	:CState(MONSTER_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{

}

void CTraceState::update()
{
	// Å¸°ÙÆÃ µÈ Player¸¦ ÂÑ¾Æ°£´Ù.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurrScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	vMonPos += vDir * GetMonster()->GetInfo().fSpeed * DeltaTimef;

	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

