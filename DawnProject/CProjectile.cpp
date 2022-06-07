#include "pch.h"
#include "CProjectile.h"

CProjectile::CProjectile()
	:m_fdir(0.f)
{

}

CProjectile::~CProjectile()
{

}

float CProjectile::GetDir()
{
	return m_fdir;
}

void CProjectile::SetDir(float _dir)
{
	m_fdir = _dir;
}

void CProjectile::update()
{

}

void CProjectile::render(HDC _dc)
{

}
