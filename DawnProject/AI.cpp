#include "pch.h"
#include "AI.h"
#include "CState.h"

AI::AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(m_mapMonsterState);
}

void AI::update()
{
	m_pCurState->update();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapMonsterState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState* AI::GetState(MONSTER_STATE _eState)
{
	map<MONSTER_STATE, CState*>::iterator iter = m_mapMonsterState.find(_eState);
	if (iter == m_mapMonsterState.end())
		return nullptr;
	else
		return iter->second;
}
