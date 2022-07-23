#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"
CRigidBody::CRigidBody()
	: m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(200.f, 600.f))
	, m_bGravity(true)
	, m_bGround(false)
	, m_vAccelA(Vec2(0, 0))
{
}

CRigidBody::~CRigidBody()
{
}

CRigidBody::CRigidBody(const CRigidBody& _origin)
	: m_fMass(_origin.m_fMass)
	, m_bGravity(_origin.m_bGravity)
	, m_bGround(false)
	, m_fFricCoeff(_origin.m_fFricCoeff)
	, m_vAccelA(Vec2(0, 0))
{

}



void CRigidBody::finalupdate()
{

	if (IsGravity() && IsGround() == false)
		update_gravity();

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
	}

	// �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	//�ӵ�
	m_vVelocity += m_vAccel * DeltaTimef;


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
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);

	//�ӵ��� ���� �̵�
	Move();

	//���ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	//�߰� ���ӵ�(�߷�) �ʱ�ȭ
	m_vAccelA = Vec2(0.f, 0.f);

	//���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
}

void CRigidBody::SetGround(bool _bGround)
{
	m_bGround = _bGround;
	if (IsGround())
		SetVelocity(Vec2(m_vVelocity.x, 0.f));
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
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 980.f));
}

