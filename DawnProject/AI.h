#pragma once

class CMonster;
class CState;

class AI
{
private:
	map<MONSTER_STATE, CState*>		m_mapMonsterState;
	CMonster*						m_pOwner;
	CState*							m_pCurState;

public:
	void update();
	
public:
	void AddState(CState* _state);
	void SetCurState(MONSTER_STATE _eState);
	CState* GetState(MONSTER_STATE _eState);

	void ChangeState(MONSTER_STATE _eNext);
	
	CMonster* GetOwner() { return m_pOwner; }
public:
	AI();
	~AI();

	friend class CMonster;
};

