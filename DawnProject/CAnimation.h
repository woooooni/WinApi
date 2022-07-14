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
	wstring					m_strName;		//	애니메이션 이름.
	CAnimator*				m_pAnimator;	//	애니메이터.
	CTexture*				m_pTex;			//	애니메이션이 사용할 텍스쳐.
	vector<tAnimFrame>		m_vecFrame;		//	애니메이션 프레임 정보.
	int						m_iCurFrm;		//	현재 프레임.
	float					m_fAccTime;		//	누적시간.


	bool					m_bFinish;		// 애니메이션이 끝났음을 알려주기위한 변수.

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

