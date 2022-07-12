#pragma once

class CState;

class AI
{
private:
	map<MONSTER_STATE, CState*>		m_mapMonsterState;
	CObject*						m_pOwner;
	CState*							m_pCurState;
public:
	void update();
	
public:
	void AddState(CState* _state);
	CState* GetState(MONSTER_STATE _eState);

public:
	AI();
	~AI();

	friend class CMonster;
};

