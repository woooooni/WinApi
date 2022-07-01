#pragma once

class CAnimator;
class CTexture;

struct tAnimFrame
{
	Vec2	vLT;
	Vec2	vSlice;
	float	fDuration;
};

class CAnimation
{
private:
	wstring					m_strName;		//	�ִϸ��̼� �̸�.
	CAnimator*				m_pAnimator;	//	�ִϸ�����.
	CTexture*				m_pTex;			//	�ִϸ��̼��� ����� �ؽ���.
	vector<tAnimFrame>		m_vecFrame;		//	�ִϸ��̼� ������ ����.
	int						m_iCurFrm;		//	���� ������.
	float					m_fAccTime;		//	�����ð�.


	bool					m_bFinish;		// �ִϸ��̼��� �������� �˷��ֱ����� ����.

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	const wstring& GetName() { return m_strName; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	bool IsFinish() { return m_bFinish; }

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

