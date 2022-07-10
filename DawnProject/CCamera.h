#pragma once
class CObject;
class CTexture;
enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKE,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT	eEffect;
	float		fDuration;
	float		fCurTime;
};

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2					m_vLookAt;				//	카메라가 보는 위치.
	Vec2					m_vPrevLookAt;			//	카메라가 보는 이전프레임 위치.
	Vec2					m_vCurLookAt;			//	이전 위치와 현재 위치 보정 위치.
	

	CObject*				m_pTargetObj;			//	카메라 타겟 오브젝트.
	Vec2					m_vDiff;				//	해상도 중심위치와 카메라 LookAt간의 차이 값.

	float					m_fTime;				// 타겟을 따라가는데 걸리는 시간.
	float					m_fSpeed;				// 타겟을 따라가는 속도.
	float					m_fAccTime;				// 타겟을 따라가는데 들었던 누적시간.

	list<tCamEffect>		m_lCamEffect;
	CTexture* m_pVeilTex;				// 카메라 가림막(검은색)

public:
	void SetLookAt(Vec2 _vLook) 
	{
		m_vLookAt = _vLook; 
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0;
	}
	void SetTarget(CObject* _obj) { m_pTargetObj = _obj; }
	Vec2 GetLookAt(){ return m_vCurLookAt; }

	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos){ return _vRenderPos + m_vDiff; }


	void FadeIn(float _fDuration)
	{
		if (0.f == _fDuration)
			assert(nullptr);

		tCamEffect eft = {};
		eft.eEffect = CAM_EFFECT::FADE_IN;
		eft.fDuration = _fDuration;
		eft.fCurTime = 0.f;
		m_lCamEffect.push_back(eft);
	}

	void FadeOut(float _fDuration)
	{
		if (0.f == _fDuration)
			assert(nullptr);

		tCamEffect eft = {};
		eft.eEffect = CAM_EFFECT::FADE_OUT;
		eft.fDuration = _fDuration;
		eft.fCurTime = 0.f;

		m_lCamEffect.push_back(eft);
	}

private:
	void CalDiff();

public:
	void Init();
	void update();
	void render(HDC _dc);
};

