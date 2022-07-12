#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "func.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(.5f)
	, m_pVeilTex(nullptr)
{

}

CCamera::~CCamera()
{
}


void CCamera::Init()
{
	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
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

	//if (KEY_HOLD(KEY::UP))
	//	m_vLookAt.y -= 500.f * DeltaTimef;
	//if (KEY_HOLD(KEY::DOWN))
	//	m_vLookAt.y += 500.f * DeltaTimef;
	//if (KEY_HOLD(KEY::LEFT))
	//	m_vLookAt.x -= 500.f * DeltaTimef;
	//if (KEY_HOLD(KEY::RIGHT))
	//	m_vLookAt.x += 500.f * DeltaTimef;
		
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	if (m_lCamEffect.empty())
		return;

	tCamEffect& effect = m_lCamEffect.front();
	effect.fCurTime += DeltaTimef;

	

	float fRatio = 0.f;
	//func.h clamp();
	fRatio = clamp(effect.fCurTime / effect.fDuration, 0.f, 1.f);
	
	int iAlpha = 0;
	if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	else if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}

	


	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;
	AlphaBlend(_dc, 0, 0
		, (int)(m_pVeilTex->Width())
		, (int)(m_pVeilTex->Height())
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)(m_pVeilTex->Width())
		, (int)(m_pVeilTex->Height())
		, bf);


	if (effect.fDuration < effect.fCurTime)
	{
		m_lCamEffect.pop_front();
	}
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

