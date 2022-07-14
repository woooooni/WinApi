#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"
CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(200.f)
	, m_fMaxSpeed(200.f)
	, m_bGravity(true)
{
}

CRigidBody::~CRigidBody()
{
}

CRigidBody::CRigidBody(const CRigidBody& _origin)
	: m_pOwner(_origin.m_pOwner)
	, m_fMass(_origin.m_fMass)
{
}



void CRigidBody::finalupdate()
{

	if (IsGravity())
	{
		update_gravity();
	}



	//힘의 크기
	float fForce = m_vForce.Length();
	if (0.f != fForce)
	{
		//힘의 방향
		m_vForce.Normalize();

		//가속도의 크기
		float m_fAccel = fForce / m_fMass;

		//가속도
		m_vAccel = m_vForce * m_fAccel;//m_vAccel = m_vForce * m_fAccel;

		//속도
		m_vVelocity += m_vAccel * DeltaTimef;	
	}

	//마찰력에 의한 반대방향으로의 가속도 적용.
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * DeltaTimef;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			//마찰 가속도가 본래 속도보다 큰 경우
			m_vVelocity = Vec2(0, 0);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	//속도제한 검사
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	//속도에 따른 이동
	Move();

	//힘초기화
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	//이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		//이동방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();
		vPos += m_vVelocity * DeltaTimef;
		m_pOwner->SetPos(vPos);
	}
}

void CRigidBody::update_gravity()
{

}

