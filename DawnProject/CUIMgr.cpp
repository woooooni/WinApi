#include "pch.h"
#include "CUI.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"

CUIMgr::CUIMgr()
{

}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObejct(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	bool bRbtnTap = KEY_TAP(KEY::RBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);
		if (nullptr != pUI)
		{
			pUI->MouseOn();
			if (bLbtnTap)
			{
				pUI->MouseLBtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLBtnUp();
				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLBtnClicked();
				}
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	/* 1. �θ� UI����, ��� �ڽ��� �˻��Ѵ�. 
	* sol1.) ����Լ��� �ڽ��� �ڽ��� �ڽ� ... �� �˻��ϱ�.
	* sol2.) Queue�� BFS(�ʺ� �켱 Ž��)�� ������ ���������� ��ȸ. => list�� ������.
	*/
	CUI* pTargetUI = nullptr;
	list<CUI*> queue;
	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		//1. ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();
		

		//2. ť���� ������ UI�� TargetUI���� Ȯ��.
		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
		}
		else
		{
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}

		

		//3. �ش� UI�� �ڽ�UI�� ������ �ִٸ�, ��� ť�� �߰�.
		const vector<CUI*>& vecChildren = pUI->GetChildrenUI();
		for (size_t i = 0; i < vecChildren.size(); i++)
		{
			queue.push_back(vecChildren[i]);
		}
	}
	

	// 2. Ÿ�� UI�� �߿��� ���� ����(���� ����) �ڽ� UI�� �켱������ ���� ����.
	return pTargetUI;
}
