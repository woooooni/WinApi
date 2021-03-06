#pragma once
#include "global.h"
#include "CCamera.h"

class CComponent;
class CCollider;
class CAnimator;
class CRigidBody;
class CStateMachine;

class CObject
{
private:
	wstring			m_strName;
	Vec2			m_vPos;
	Vec2			m_vScale;
	GROUP_TYPE		m_eType;

	CComponent*		m_arrComponent[(UINT)COMPONENT_TYPE::END];
	bool			m_bAlive;


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring& GetName() { return m_strName; }

	void SetType(GROUP_TYPE _eType) { m_eType = _eType; }
	GROUP_TYPE GetType() { return m_eType; }

	bool IsDead(){ return !m_bAlive; }

public:
	void CreateCollider();
	CCollider* GetCollider() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}


	void CreateAnimator();
	CAnimator* GetAnimator() { return (CAnimator*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }

	void CreateRigidBody();
	CRigidBody* GetRigidBody() { return (CRigidBody*)m_arrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY]; }

	void CreateStateMachine();
	CStateMachine* GetStateMachine() { return (CStateMachine*)m_arrComponent[(UINT)COMPONENT_TYPE::STATEMACHINE]; }

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void init() {}
	virtual void update()=0;
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public: 
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
};

