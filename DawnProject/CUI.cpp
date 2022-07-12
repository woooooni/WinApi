#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_bRbtnDown(false)
	, m_strText(L"")
{
	
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_bRbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); i++)
	{
		AddChild((CUI*)_origin.m_vecChildUI[i]->Clone());
	}
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

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	SetBkMode(_dc, TRANSPARENT);
	RECT rt = { (int)vPos.x , (int)vPos.y , (int)(vPos.x + vScale.x),  (int)(vPos.y + vScale.y) };
	DrawText(_dc, m_strText.c_str(), m_strText.length(), &rt, DT_CENTER|DT_VCENTER);
	SetBkMode(_dc, OPAQUE);

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
