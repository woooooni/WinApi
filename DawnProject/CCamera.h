#pragma once

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vLookAt;		//	ī�޶� ���� ��ġ.
	Vec2		m_vPrevLookAt;	//	ī�޶� ���� ���������� ��ġ.
	Vec2		m_vCurLookAt;	//	���� ��ġ�� ���� ��ġ ���� ��ġ.
	

	CObject*	m_pTargetObj;	//	ī�޶� Ÿ�� ������Ʈ.
	Vec2		m_vDiff;		//	�ػ� �߽���ġ�� ī�޶� LookAt���� ���� ��.

	float		m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�.
	float		m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�.
	float		m_fAccTime;		// Ÿ���� ���󰡴µ� ����� �����ð�.

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

