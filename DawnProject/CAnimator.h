#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// ��� �ִϸ��̼�.
	CAnimation*					m_pCurAnim;		// ���� ������� �ִϸ��̼�.
	CObject*					m_pOwner;		// Animator ���� ������Ʈ.
	bool						m_bRepeat;		// �ݺ���� ����.
	bool						m_bFlipX;		// �¿���� ����.
	bool						m_bFlipY;		// ���Ϲ��� ����.

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

