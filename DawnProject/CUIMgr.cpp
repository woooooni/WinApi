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
	// 1. FocusedUI 확인.
	m_pFocusedUI = GetFocusedUI();
	if (!m_pFocusedUI)
	{
		return;
	}
		

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI들 중 실제 타겟팅 된 UI를 가져온다.
	
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
	//즉시 포커스
	//이미 포커싱 중인 UI거나, 포커싱 해제요청인 경우.
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

	//vector내에서 맨 뒤로 순번 교체.
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

	// 왼쪽 버튼 TAP이 발생했다는 전제.
	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}


	// 이번에 focus된 UI가 없다면,
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetIter;

	//vector내에서 맨 뒤로 순번 교체.
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	/* 1. 부모 UI포함, 모든 자식을 검사한다. 
	* sol1.) 재귀함수로 자식의 자식의 자식 ... 을 검사하기.
	* sol2.) Queue로 BFS(너비 우선 탐색)를 구현해 계층단위로 순회. => list가 최적임.
	*/
	CUI* pTargetUI = nullptr;
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTargetUI;//	타겟이 아닌 UI를 모아 놓고, 이 벡터 안의 UI들에 대해 따로 처리.

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		//1. 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();
		

		//2. 큐에서 꺼내온 UI가 TargetUI인지 확인.
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

		//3. 해당 UI가 자식UI를 가지고 있다면, 모두 큐에 추가.
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
	
	

	// 2. 타겟 UI들 중에서 제일 끝단(낮은 계층) 자식 UI가 우선순위가 제일 높다.
	return pTargetUI;
}
