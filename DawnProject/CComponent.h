#pragma once

class CObject;
class CComponent
{
private:
	
protected:
	CObject* m_pOwner;		//�ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ

public:
	virtual void finalupdate() = 0;
	virtual void render(HDC _dc) = 0;

public:
	CObject* GetObj() { return m_pOwner; }
	
public:
	CComponent();
	~CComponent();
	CComponent(const CComponent& _origin);
	friend class CObject;
};

