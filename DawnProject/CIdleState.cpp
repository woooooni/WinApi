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
	// 1. ������ �ֱ�.
	// 2. �÷��̾��� ��ġ üũ.
	// 3. ���� ���� �ȿ� ������ �������·� ��ȯ.
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{
}

