#pragma once


class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END]; //¸ðµç ¾À ¸ñ·Ï
	CScene*		m_pCurScene; //ÇöÀç ¾À

public:
	void Init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurrScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

