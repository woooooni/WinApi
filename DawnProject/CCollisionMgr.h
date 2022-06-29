#pragma once
class CCollider;

union COLLIDER_ID
{
	//TODO::구조체, union 공부
	struct
	{
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	map<ULONGLONG, bool>		m_mapColInfo;//충돌체 간의 이전 프레임 충돌 정보(두 충돌체간의 고유한 키값이 필요함)
	UINT						m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 matrix

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

