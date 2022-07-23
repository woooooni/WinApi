#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CStateMachine.h"


CObject::CObject()
	:m_vPos{}
	, m_vScale{}
	, m_bAlive(true)
	, m_eType(GROUP_TYPE::DEFAULT)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		m_arrComponent[i] = nullptr;
	}
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_arrComponent{}
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_bAlive(true)
	, m_eType(_origin.m_eType)
{

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != _origin.m_arrComponent[i])
			m_arrComponent[i] = _origin.m_arrComponent[i];
	}
}

CObject::~CObject()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++) 
	{
		if (nullptr != m_arrComponent[i])
			delete m_arrComponent[i];
	}
}


void CObject::CreateCollider()
{
	m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER] = new CCollider;
	m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR] = new CAnimator;
	m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_arrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY] = new CRigidBody;
	m_arrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY]->m_pOwner = this;
}

void CObject::CreateStateMachine() 
{
	m_arrComponent[(UINT)COMPONENT_TYPE::STATEMACHINE] = new CStateMachine;
	m_arrComponent[(UINT)COMPONENT_TYPE::STATEMACHINE]->m_pOwner = this;
}

void CObject::update()
{
	
}

void CObject::finalupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != m_arrComponent[i])
			m_arrComponent[i]->finalupdate();
	}
}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);
	Rectangle(_dc,
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f),
		(int)(vRenderPos.y + m_vScale.y / 2.f));

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != m_arrComponent[i])
			m_arrComponent[i]->render(_dc);
	}
}

