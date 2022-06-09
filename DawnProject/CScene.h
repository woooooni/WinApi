#pragma once

class CObject; //���� ���� => ������ �ӵ��� ������ ���� ����.

class CScene
{

private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene �̸�
	

public:
	void SetName(const wstring& _strName);
	const wstring& GetName();


	void update();
	void render(HDC _dc);



	virtual void Enter() = 0; // ���� �����Լ� �ش� Scene�� ���� �� ȣ��.
	virtual void Exit() = 0; // ���� �����Լ� �ش� Scene���� ��� ��� ȣ��.


public:
	void AddObject(CObject* _obj, GROUP_TYPE _type);


public:
	CScene();
	virtual ~CScene();
};

