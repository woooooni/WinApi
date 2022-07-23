#pragma once

#include "CComponent.h"

class CObject;

class CRigidBody :
	public CComponent
{
private:
	// F = M * A;
	// V += A * DT
	Vec2		m_vForce;		//	ũ��, ���� ����
	Vec2		m_vAccel;		//	���ӵ�
	Vec2		m_vAccelA;		//  ���ӵ� �߰���CComponent
	Vec2		m_vVelocity;	//	�ӵ�(�ӷ� + ����)
	Vec2		m_vMaxVelocity;	//	�ִ�ӵ�

	float		m_fMass;		//	����
	float		m_fFricCoeff;	//	�������

	bool		m_bGravity;		//	�߷� ���� ����
	bool		m_bGround;		//	�ٴڿ� �پ��ִ��� ����


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

