#include "pch.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CIdleState.h"

CIdleState::CIdleState()
	:CState(MONSTER_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// 1. 가만히 있기.
	// 2. 플레이어의 위치 체크.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurrScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 3. 몬스터 범위 안에 들어오면 추적상태로 전환.
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();


	//플레이어가 몬스터의 인식범위 안으로 진입했을 때.
	if (fLen < pMonster->GetInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{
}

