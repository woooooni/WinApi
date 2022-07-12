#pragma once

class CObject; //���� ���� => ������ �ӵ��� ������ ���� ����.

class CScene
{

private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene �̸�
	
	UINT				m_iTileX;	//Ÿ�� ���ΰ���
	UINT				m_iTileY;	//Ÿ�� ���ΰ���

public:
	void SetName(const wstring& _strName);
	const wstring& GetName();

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

public:
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);	//������ ����


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

	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

