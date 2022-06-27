#pragma once
class CCollider;

class CObject
{
private:
	wstring		m_strName;
	Vec2		m_vPos;
	Vec2		m_vScale;

	//Collider(충돌) 컴포넌트
	CCollider*	m_pCollider;

	bool		m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring& GetName() { return m_strName; }

	bool IsDead(){ return !m_bAlive; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update()=0;
	virtual void finalupdate() final;

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

public: 
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

