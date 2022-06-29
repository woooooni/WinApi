#include "pch.h"
#include "CProjectile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CObject.h"
#include "func.h"

CProjectile::CProjectile()
	:m_fTheta(PI / 2.f)
	,m_vDir(Vec2(1.f, 1.f))
	,m_fSpeed(600.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
	m_vDir.Normalize();
	
}

CProjectile::~CProjectile()
{
	
}

void CProjectile::update()
{
	Vec2 vPos = GetPos();

	/*vPos.x += 600.f * cosf(m_fTheta) * DeltaTimef;
	vPos.y += 600.f * sinf(m_fTheta) * DeltaTimef;*/

	vPos.x += m_fSpeed * cosf(m_vDir.x) * DeltaTimef;
	vPos.y += m_fSpeed * sinf(m_vDir.y) * DeltaTimef;

	SetPos(vPos);
}

void CProjectile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc,
		(int)vPos.x - vScale.x / 2,
		(int)vPos.y - vScale.y / 2,
		(int)vPos.x + vScale.x / 2,
		(int)vPos.y + vScale.y / 2);

	component_render(_dc);
}

void CProjectile::OnCollision(CCollider* _pOther)
{
}

void CProjectile::OnCollisionEnter(CCollider* _other)
{
	if (_other->GetObj()->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}

void CProjectile::OnCollisionExit(CCollider* _pOther)
{
	int a = 0;
}


