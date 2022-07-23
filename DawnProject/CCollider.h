#pragma once
#include "CComponent.h"

class CObject;
class CCollider
	: public CComponent
{

private:
	static UINT g_iNextId;

	Vec2		m_vOffsetPos;	//오브젝트로부터의 상대적 위치
	Vec2		m_vFinalPos;	//오브젝트 마지막 위치
	Vec2		m_vScale;		//Collider의 크기

	UINT		m_iId;			//Collider 고유 아이디
	PEN_TYPE	ePenType;

	bool		m_bTrigger;		//Collider 충돌 시, 밀어낼지 여부
	bool		m_bActive;		//Collider 활성/비활성

public:

	UINT GetId() { return m_iId; }

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	
	Vec2 GetFinalPos() { return m_vFinalPos; }
	void SetTrigger(bool _bTrigger) { m_bTrigger = _bTrigger; }
public:
	virtual void finalupdate();
	virtual void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);					// 충돌 중 인경우 호출되는 함수.
	void OnCollisionEnter(CCollider* _pOther);				// 충돌체가 진입한 경우 호출되는 함수.
	void OnCollisionExit(CCollider* _pOther);				// 충돌체가 빠져나간 경우 호출되는 함수.
	CCollider& operator = (CCollider& _origin) = delete;	// operator 함수 삭제. Default도 생성되지 않음.


private:
	void PushOutInterSection(CCollider* _pOther);
	RECT GetInterSection(CCollider* _pOther);

public:
	CCollider();
	~CCollider();
	CCollider(const CCollider& _origin);

};

