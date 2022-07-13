#include "pch.h"
#include "AI.h"
#include "CObject.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CIdleState.h";
#include "CTraceState.h"
#include "CMonsterFactory.h"

CMonster* CMonsterFactory::CreateMonster(MONSTER_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;
	switch (_eType)
	{
	case MONSTER_TYPE::NORMAL: 
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonsterInfo info = {};
		info.fAtt = 10.f;
		info.fDef = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		/*AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);*/
	}
		break;
	case MONSTER_TYPE::RANGE:
	{

	}
		break;
	default:
		break;
	}

	assert(pMon);

	return pMon;
}
