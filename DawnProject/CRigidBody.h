#pragma once

#include "CComponent.h"

class CObject;

class CRigidBody :
	public CComponent
{
private:
	// F = M * A;
	// V += A * DT
	Vec2		m_vForce;		//	크기, 방향 벡터
	Vec2		m_vAccel;		//	가속도
	Vec2		m_vAccelA;		//  가속도 추가량CComponent
	Vec2		m_vVelocity;	//	속도(속력 + 방향)
	Vec2		m_vMaxVelocity;	//	최대속도

	float		m_fMass;		//	질량
	float		m_fFricCoeff;	//	마찰계수

	bool		m_bGravity;		//	중력 영향 여부
	bool		m_bGround;		//	바닥에 붙어있는지 여부


public:
	void AddForce(Vec2 _vForce){ m_vForce += _vForce; }

	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }

	void AddVelocity(Vec2 _velocity) { m_vVelocity += _velocity; }
	void SetVelocity(Vec2 _velocity) { m_vVelocity = _velocity; }
	Vec2 GetVelocity() { return m_vVelocity; }
	void SetMaxVelocity(Vec2 _vVelocity) { m_vMaxVelocity = _vVelocity; }
	
	void SetAccelAlpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }
	float GetSpeed(){ return m_vVelocity.Length(); }
	

	void SetGravity(bool _bGravity) { m_bGravity = _bGravity; }
	bool IsGravity() { return m_bGravity; }

	void SetGround(bool _bGround);
	bool IsGround() { return m_bGround; }

private:
	void Move();


private:
	void update_gravity();

public:
	virtual void finalupdate();
	virtual void render(HDC _dc) { };



public:
	CRigidBody();
	~CRigidBody();
	CRigidBody(const CRigidBody& _origin);
};

