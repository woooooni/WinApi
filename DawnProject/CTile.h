#pragma once
#include "global.h"
#include "CObject.h"
#include "CTexture.h"

class CTile:
	public CObject
{
private:
	CTexture*	m_pTileTexture;
	int			m_iIdx;

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTexture = _pTex;
	}

	void AddImgIdx()
	{
		++m_iIdx;
	}
public:
	virtual void render(HDC _dc);
	virtual void update();
	CLONE(CTile);

public:
	CTile();
	~CTile();
};

