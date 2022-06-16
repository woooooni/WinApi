#pragma once
class CObject;

class CCollider
{
private:
	CObject*	m_pOwner;		//Collider를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos;	//오브젝트로부터의 상대적 위치
	Vec2		m_vFinalPos;	//마지막 위치
	Vec2		m_vScale;		//충돌체의 크기

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScal(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate();
	friend class CObject;

public:
	CCollider();
	~CCollider();
};

