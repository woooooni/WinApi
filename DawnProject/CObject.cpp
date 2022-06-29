#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"


CObject::CObject()
	:m_vPos{}
	, m_vScale{}
	, m_pCollider{}
	, m_bAlive(true)
{
	
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_bAlive(true)
{
	m_pCollider = new CCollider(*_origin.m_pCollider);
	m_pCollider->m_pOwner = this;
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}


void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::update()
{
	
}

void CObject::finalupdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->finalupdate();
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc,
		(int)(m_vPos.x - m_vScale.x / 2.f),
		(int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f),
		(int)(m_vPos.y + m_vScale.y / 2.f));

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}
}

