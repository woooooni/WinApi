#pragma once

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vLookAt;		//	카메라가 보는 위치.
	Vec2		m_vPrevLookAt;	//	카메라가 보는 이전프레임 위치.
	Vec2		m_vCurLookAt;	//	이전 위치와 현재 위치 보정 위치.
	

	CObject*	m_pTargetObj;	//	카메라 타겟 오브젝트.
	Vec2		m_vDiff;		//	해상도 중심위치와 카메라 LookAt간의 차이 값.

	float		m_fTime;		// 타겟을 따라가는데 걸리는 시간.
	float		m_fSpeed;		// 타겟을 따라가는 속도.
	float		m_fAccTime;		// 타겟을 따라가는데 들었던 누적시간.

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

private:
	void CalDiff();

public:
	void update();

};

