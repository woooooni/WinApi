#include "pch.h"
#include "CCollisionMgr.h"

CCollisionMgr::CCollisionMgr() 
	:m_arrCheck{}
{	
}

CCollisionMgr::~CCollisionMgr() 
{
}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//_eLeft, _eRight 중 더 작은 수를 행으로 잡아야 함.
	//큰 값을 열(비트)로 잡아야 함.
}

void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}
