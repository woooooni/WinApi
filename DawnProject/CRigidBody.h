#pragma once

class CObject;

class CRigidBody
{
private:
	// F = M * A;
	// V += A * DT

	CObject*	m_pOwner;		//	RigidBody�� �����ϰ� �ִ� ������Ʈ.
	
	Vec2		m_vForce;		//	ũ��, ���� ����
	Vec2		m_vAccel;		//	���ӵ�
	Vec2		m_vVelocity;	//	�ӵ�(�ӷ� + ����)
	

	float		m_fMass;		//	����
	float		m_fFricCoeff;	//	�������
	float		m_fMaxSpeed;	//	�ִ�ӵ�

	bool		m_bGravity;		// �߷� ���� ����
	bool		m_bGround;		// �ٴڿ� �پ��ִ��� ����


public:
	void AddForce(Vec2 _vForce){ m_vForce += _vForce; }

	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }

	void AddVelocity(Vec2 _velocity) { m_vVelocity += _velocity; }
	void SetVelocity(Vec2 _velocity) { m_vVelocity = _velocity; }

	float GetSpeed(){ return m_vVelocity.Length(); }
	void SetMaxVelocity(float _fVelocity) { m_fMaxSpeed = _fVelocity; }

	void SetGravity(bool _bGravity) { m_bGravity = _bGravity; }
	bool IsGravity() { return m_bGravity; }

	void SetGround(bool _bGround) { m_bGround = _bGround; }

private:
	void Move();


private:
	void update_gravity();
public:
	void finalupdate();




public:
	CRigidBody();
	~CRigidBody();
	CRigidBody(const CRigidBody& _origin);

	friend class CObject;
};

