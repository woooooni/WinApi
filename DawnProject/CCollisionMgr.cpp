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
	//_eLeft, _eRight �� �� ���� ���� ������ ��ƾ� ��.
	//ū ���� ��(��Ʈ)�� ��ƾ� ��.
}

void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}
