#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
{
	
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();
	if (nullptr != GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	MouseOnCheck();
	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	Rectangle(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRenderPos(vMousePos);
	}
	
	if (m_vFinalPos.x <= vMousePos.x && m_vFinalPos.x + vScale.x >= vMousePos.x
		&& m_vFinalPos.y <= vMousePos.y && m_vFinalPos.y + vScale.y >= vMousePos.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

}

//Mouse Events
void CUI::MouseOn()
{
}

void CUI::MouseLBtnDown()
{
}

void CUI::MouseLBtnUp()
{
}

void CUI::MouseLBtnClicked()
{
}

void CUI::MouseRBtnDown()
{
}

void CUI::MouseRBtnUP()
{
}

void CUI::MouseRBtnClicked()
{
}
