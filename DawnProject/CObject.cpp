#include "pch.h"
#include "CObject.h"

CObject::CObject()
	:m_vPos{}
	, m_vScale{}
{
	
}

CObject::~CObject()
{
		
}

void CObject::SetPos(Vec2 _vPos)
{
	m_vPos = _vPos;
}

void CObject::SetScale(Vec2 _vScale)
{
	m_vScale = _vScale;
}

Vec2 CObject::GetPos()
{
	return m_vPos;
}

Vec2 CObject::GetScale()
{
	return m_vScale;
}