#pragma once

#include "CComponent.h"
class CAnimation;
class CTexture;

class CAnimator
	: public CComponent
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// ��� �ִϸ��̼�.
	CAnimation*					m_pCurAnim;		// ���� ������� �ִϸ��̼�.
	bool						m_bRepeat;		// �ݺ���� ����.
	bool						m_bFlipX;		// �¿���� ����.
	bool						m_bFlipY;		// ���Ϲ��� ����.

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, 
							Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, 
							float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void LoadAnimation(const wstring& _strRelativePath);
	void Play(const wstring& _strName, bool _bRepeat);

	void SetFlipX(bool _bFlipX) { m_bFlipX = _bFlipX; }
	void SetFlipY(bool _bFlipY) { m_bFlipY = _bFlipY; }

	bool GetFlipX() { return m_bFlipX; }
	bool GetFlipY() { return m_bFlipY; }

public:
	void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	CLONE(CAnimator);
public:
	CAnimator();
	~CAnimator();
};

