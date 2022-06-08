#pragma once
class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

public:
	void SetPos(Vec2 _vPos);
	void SetScale(Vec2 _vScale);

	Vec2 GetPos();
	Vec2 GetScale();

public:
	virtual void update()=0;
	virtual void render(HDC _dc)=0;


public: 
	CObject();
	virtual ~CObject();
};

