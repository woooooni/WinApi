#pragma once
class CObject;

class CCollider
{

private:
	static UINT g_iNextId;
	CObject*	m_pOwner;		//Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	//������Ʈ�κ����� ����� ��ġ
	Vec2		m_vFinalPos;	//������Ʈ ������ ��ġ
	Vec2		m_vScale;		//Collider�� ũ��

	UINT		m_iId;			//Collider ���� ���̵�

public:

	UINT GetId() { return m_iId; }

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }
public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);					// �浹 �� �ΰ�� ȣ��Ǵ� �Լ�.
	void OnCollisionEnter(CCollider* _pOther);				// �浹ü�� ������ ��� ȣ��Ǵ� �Լ�.
	void OnCollisionExit(CCollider* _pOther);				// �浹ü�� �������� ��� ȣ��Ǵ� �Լ�.
	CCollider& operator = (CCollider& _origin) = delete;	// operator �Լ� ����. Default�� �������� ����.

public:
	CCollider();
	~CCollider();
	CCollider(const CCollider& _origin);

	friend class CObject;
};

