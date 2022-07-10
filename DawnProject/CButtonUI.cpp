#include "CButtonUI.h"

CButtonUI::CButtonUI()
	:CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CButtonUI::~CButtonUI()
{
}


//button event
void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLBtnDown()
{
}

void CButtonUI::MouseLBtnUp()
{
}

void CButtonUI::MouseLBtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (nullptr != m_pSceneFunc && nullptr != m_pSceneInst)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}
