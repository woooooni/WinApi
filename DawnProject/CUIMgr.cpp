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

	/* 1. 부모 UI포함, 모든 자식을 검사한다. 
	* sol1.) 재귀함수로 자식의 자식의 자식 ... 을 검사하기.
	* sol2.) Queue로 BFS(너비 우선 탐색)를 구현해 계층단위로 순회. => list가 최적임.
	*/
	CUI* pTargetUI = nullptr;
	list<CUI*> queue;
	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		//1. 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();
		

		//2. 큐에서 꺼내온 UI가 TargetUI인지 확인.
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

		

		//3. 해당 UI가 자식UI를 가지고 있다면, 모두 큐에 추가.
		const vector<CUI*>& vecChildren = pUI->GetChildrenUI();
		for (size_t i = 0; i < vecChildren.size(); i++)
		{
			queue.push_back(vecChildren[i]);
		}
	}
	

	// 2. 타겟 UI들 중에서 제일 끝단(낮은 계층) 자식 UI가 우선순위가 제일 높다.
	return pTargetUI;
}
