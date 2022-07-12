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
	// 1. ������ �ֱ�.
	// 2. �÷��̾��� ��ġ üũ.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurrScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 3. ���� ���� �ȿ� ������ �������·� ��ȯ.
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();


	//�÷��̾ ������ �νĹ��� ������ �������� ��.
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

