#pragma once

class CAnimator;
class CTexture;

struct tAnimFrame
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
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
	bool IsFinish() { return m_bFinish; }

	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	tAnimFrame& GetFrame(int _iIdx) { return m_vecFrame[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrame.size(); }

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);


private:
	void draw(HDC _dc, Vec2 _vRenderPos);
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

