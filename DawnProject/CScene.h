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


	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);



	virtual void Enter() = 0; // ���� �����Լ� �ش� Scene�� ���� �� ȣ��.
	virtual void Exit() = 0; // ���� �����Լ� �ش� Scene���� ��� ��� ȣ��.


public:
	void AddObject(CObject* _obj, GROUP_TYPE _eType) 
	{ 
		m_arrObj[(UINT)_eType].push_back(_obj); 
	}

	const vector<CObject*>& GetGroupObejct(GROUP_TYPE _eType)
	{ 
		return m_arrObj[(UINT)_eType]; 
	}

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

public:
	CScene();
	virtual ~CScene();
};

