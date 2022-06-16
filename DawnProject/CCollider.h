#pragma once
class CObject;

class CCollider
{
private:
	CObject*	m_pOwner;		//Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	//������Ʈ�κ����� ����� ��ġ
	Vec2		m_vFinalPos;	//������ ��ġ
	Vec2		m_vScale;		//�浹ü�� ũ��

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

