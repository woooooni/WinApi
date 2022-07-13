#pragma once

class CObject;

class CRigidBody
{
private:
	// F = M * A;
	// V += A * DT

	CObject*	m_pOwner;		//	RigidBody를 소유하고 있는 오브젝트.
	
	Vec2		m_vForce;		//	크기, 방향 벡터
	Vec2		m_vAccel;		//	가속도
	Vec2		m_vVelocity;	//	속도(속력 + 방향)
	

	float		m_fMass;		//	질량
	float		m_fFricCoeff;		//	마찰계수
	float		m_fMaxSpeed;	//	최대속도


public:
	void AddForce(Vec2 _vForce){ m_vForce += _vForce; }

	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }

	void AddVelocity(Vec2 _velocity) { m_vVelocity += _velocity; }
	void SetVelocity(Vec2 _velocity) { m_vVelocity = _velocity; }
	void SetMaxVelocity(float _fVelocity) { m_fMaxSpeed = _fVelocity; }
private:
	void Move();

public:
	void finalupdate();




public:
	CRigidBody();
	~CRigidBody();
	CRigidBody(const CRigidBody& _origin);

	friend class CObject;
};

