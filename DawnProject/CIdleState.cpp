#include "pch.h"
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
	// 3. 몬스터 범위 안에 들어오면 추적상태로 전환.
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{
}

