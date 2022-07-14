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



	//���� ũ��
	float fForce = m_vForce.Length();
	if (0.f != fForce)
	{
		//���� ����
		m_vForce.Normalize();

		//���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		//���ӵ�
		m_vAccel = m_vForce * m_fAccel;//m_vAccel = m_vForce * m_fAccel;

		//�ӵ�
		m_vVelocity += m_vAccel * DeltaTimef;	
	}

	//�����¿� ���� �ݴ���������� ���ӵ� ����.
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * DeltaTimef;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			//���� ���ӵ��� ���� �ӵ����� ū ���
			m_vVelocity = Vec2(0, 0);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	//�ӵ����� �˻�
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	//�ӵ��� ���� �̵�
	Move();

	//���ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	//�̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		//�̵�����
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

