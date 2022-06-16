#pragma once
class CCollider;

class CObject
{
private:
	Vec2		m_vPos;
	Vec2		m_vScale;

	//Collider(충돌) 컴포넌트
	CCollider*	m_pCollider;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void CreateCollider();

public:
	virtual void update();
	virtual void finalupdate() final;
	virtual void render(HDC _dc);
	

public: 
	CObject();
	virtual ~CObject();
};

