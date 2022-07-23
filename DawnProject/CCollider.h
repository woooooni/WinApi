#pragma once
#include "CComponent.h"

class CObject;
class CCollider
	: public CComponent
{

private:
	static UINT g_iNextId;

	Vec2		m_vOffsetPos;	//������Ʈ�κ����� ����� ��ġ
	Vec2		m_vFinalPos;	//������Ʈ ������ ��ġ
	Vec2		m_vScale;		//Collider�� ũ��

	UINT		m_iId;			//Collider ���� ���̵�
	PEN_TYPE	ePenType;

	bool		m_bTrigger;		//Collider �浹 ��, �о�� ����
	bool		m_bActive;		//Collider Ȱ��/��Ȱ��

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
	void OnCollision(CCollider* _pOther);					// �浹 �� �ΰ�� ȣ��Ǵ� �Լ�.
	void OnCollisionEnter(CCollider* _pOther);				// �浹ü�� ������ ��� ȣ��Ǵ� �Լ�.
	void OnCollisionExit(CCollider* _pOther);				// �浹ü�� �������� ��� ȣ��Ǵ� �Լ�.
	CCollider& operator = (CCollider& _origin) = delete;	// operator �Լ� ����. Default�� �������� ����.


private:
	void PushOutInterSection(CCollider* _pOther);
	RECT GetInterSection(CCollider* _pOther);

public:
	CCollider();
	~CCollider();
	CCollider(const CCollider& _origin);

};

