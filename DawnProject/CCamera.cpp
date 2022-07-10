#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(.5f)
{

}

CCamera::~CCamera()
{
}


void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;

		else
			m_vLookAt = m_pTargetObj->GetPos();
	}

	/*if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * DeltaTimef;
	if (KEY_HOLD(KEY::S))
		m_vLookAt.y += 500.f * DeltaTimef;
	if (KEY_HOLD(KEY::A))
		m_vLookAt.y -= 500.f * DeltaTimef;
	if (KEY_HOLD(KEY::D))
		m_vLookAt.y += 500.f * DeltaTimef;*/
		
	CalDiff();
}

void CCamera::CalDiff()
{
	
	m_fAccTime += DeltaTimef;
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vDir = m_vLookAt - m_vPrevLookAt;
		if (!vDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vDir.Normalize() * m_fSpeed * DeltaTimef;
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	Vec2 vCenter = vResolution / 2;


	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}


