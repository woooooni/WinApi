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
		if (pRigid == nullptr)
			return;

		pRigid->SetGround(true);

		Vec2 vObjPos = pOtherObj->GetPos();
		Vec2 vObjScale = pOtherObj->GetScale();
	}
}

