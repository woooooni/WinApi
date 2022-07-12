#pragma once

class CMonster;

enum class MONSTER_TYPE
{
	NORMAL,
	RANGE,
	FIRE,
	SAND,
	WIND,
	WATER,
};

class CMonsterFactory
{
public:
	static CMonster* CreateMonster(MONSTER_TYPE _eType, Vec2 _vPos);

private:
	CMonsterFactory() {};
	~CMonsterFactory() {};
};