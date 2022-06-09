#pragma once


class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END]; //��� �� ���
	CScene*		m_pCurScene; //���� ��

public:
	void Init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurrScene() { return m_pCurScene; }
};

