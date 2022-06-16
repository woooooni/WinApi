#include "pch.h"
#include "CCollider.h"
#include "CObject.h"

CCollider::CCollider()
{

}

CCollider::~CCollider()
{

}

void CCollider::finalupdate()
{
	//Object Follow
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;


}


