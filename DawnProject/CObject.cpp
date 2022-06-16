#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"


CObject::CObject()
	:m_vPos{}
	, m_vScale{}
	, m_pCollider{}
{
	
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

}

