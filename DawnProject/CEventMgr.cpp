#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		if(nullptr != m_vecDead[i])
			delete m_vecDead[i];
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	//�̺�Ʈ ó���Լ�
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurrScene()->AddObject(pNewObj, eType);
	}
		break;


	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// Object�� Dead ���·� ����.
		// ���� ���� ������Ʈ�� ��Ƶα�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();

		m_vecDead.push_back(pDeadObj);

	}
		break;


	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : SCENE_TYPE

		//1. Scene ����.
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		//2. ��Ŀ�� UI ����.
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	}
}
