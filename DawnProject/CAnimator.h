#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// 모든 애니메이션.
	CAnimation*					m_pCurAnim;		// 현재 재생중인 애니메이션.
	CObject*					m_pOwner;		// Animator 소유 오브젝트.
	bool						m_bRepeat;		// 반복재생 여부.
	bool						m_bFlipX;		// 좌우반전 여부.
	bool						m_bFlipY;		// 상하반전 여부.

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, 
							Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, 
							float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	CObject* GetObj() { return m_pOwner; }

	void SetFlipX(bool _bFlipX) { m_bFlipX = _bFlipX; }
	void SetFlipY(bool _bFlipY) { m_bFlipY = _bFlipY; }

	bool GetFlipX() { return m_bFlipX; }
	bool GetFlipY() { return m_bFlipY; }

public:
	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();


private:
	friend class CObject;
};

