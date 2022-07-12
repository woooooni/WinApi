#include "pch.h"
#include "CMonster.h"
#include "AI.h"
#include "CState.h"

CState::CState(MONSTER_STATE _eState)
	:m_eState(_eState)
{

}

CState::~CState()
{
	
}

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}

