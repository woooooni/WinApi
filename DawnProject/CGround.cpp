#include "pch.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CGround.h"


CGround::CGround()
{
	CreateCollider();
}

CGround::~CGround()
{

}

void CGround::init()
{
	GetCollider()->SetScale(GetScale());
}

void CGround::update()
{
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetType() == GROUP_TYPE::PLAYER)
	{
		CRigidBody* pRigid = pOtherObj->GetRigidBody();

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();
		if (pRigid == nullptr || pRigid->IsGround() == false)
			return;

		
		
		// ����� ����
		// �Լ��� �������� �ٷ� �������� ����ϸ� ������ ������� ������, ���������� ���� �޾Ƴ��� ���.
		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y += fValue;

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetType() == GROUP_TYPE::PLAYER)
	{
		CRigidBody* pRigid = pOtherObj->GetRigidBody();
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();
		if (pRigid == nullptr || pRigid->IsGround() == false)
			return;

		// ����� ����
		// �Լ��� �������� �ٷ� �������� ����ϸ� ������ ������� ������, ���������� ���� �޾Ƴ��� ���.
		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue - 1.f);

		pOtherObj->SetPos(vObjPos);
	}
}

