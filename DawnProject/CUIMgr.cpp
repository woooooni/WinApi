#include "pch.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CKeyMgr.h"


CUIMgr::CUIMgr()
	:m_pFocusedUI(nullptr)
{

}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI Ȯ��.
	m_pFocusedUI = GetFocusedUI();
	if (!m_pFocusedUI)
	{
		return;
	}
		

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI�� �� ���� Ÿ���� �� UI�� �����´�.
	
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bRbtnTap = KEY_TAP(KEY::RBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);

	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();
		if (bLbtnTap)
		{
			pTargetUI->MouseLBtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLBtnUp();
			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLBtnClicked();
			}
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	//��� ��Ŀ��
	//�̹� ��Ŀ�� ���� UI�ų�, ��Ŀ�� ������û�� ���.
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	//vector������ �� �ڷ� ���� ��ü.
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	CUI* pFocusedUI = m_pFocusedUI;
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���� ��ư TAP�� �߻��ߴٴ� ����.
	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}


	// �̹��� focus�� UI�� ���ٸ�,
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetIter;

	//vector������ �� �ڷ� ���� ��ü.
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	/* 1. �θ� UI����, ��� �ڽ��� �˻��Ѵ�. 
	* sol1.) ����Լ��� �ڽ��� �ڽ��� �ڽ� ... �� �˻��ϱ�.
	* sol2.) Queue�� BFS(�ʺ� �켱 Ž��)�� ������ ���������� ��ȸ. => list�� ������.
	*/
	CUI* pTargetUI = nullptr;
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTargetUI;//	Ÿ���� �ƴ� UI�� ��� ����, �� ���� ���� UI�鿡 ���� ���� ó��.

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		//1. ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();
		

		//2. ť���� ������ UI�� TargetUI���� Ȯ��.
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTargetUI.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}

		else
		{
			vecNoneTargetUI.push_back(pUI);
		}

		//3. �ش� UI�� �ڽ�UI�� ������ �ִٸ�, ��� ť�� �߰�.
		const vector<CUI*>& vecChildren = pUI->GetChildrenUI();
		for (size_t i = 0; i < vecChildren.size(); i++)
		{
			queue.push_back(vecChildren[i]);
		}
	}


	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTargetUI.size(); i++)
		{
			vecNoneTargetUI[i]->m_bLbtnDown = false;
		}
	}
	
	

	// 2. Ÿ�� UI�� �߿��� ���� ����(���� ����) �ڽ� UI�� �켱������ ���� ����.
	return pTargetUI;
}
