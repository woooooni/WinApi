#pragma once

class CObject; //전방 선언 => 컴파일 속도에 영향을 주지 않음.

class CScene
{

private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene 이름
	

public:
	void SetName(const wstring& _strName);
	const wstring& GetName();


	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);



	virtual void Enter() = 0; // 순수 가상함수 해당 Scene에 진입 시 호출.
	virtual void Exit() = 0; // 순수 가상함수 해당 Scene에서 벗어날 경우 호출.


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

