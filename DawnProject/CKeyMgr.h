#pragma once
#include "pch.h"


enum class KEY_STATE 
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};


enum class KEY 
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	ALT, CTRL, LSHIFT, SPACE, ENTER, ESC, 
	
	LBTN,
	RBTN,
	
	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;	// 키의 상태
	bool		bPrevPushed;	// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;

public:
	void Init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) 
	{
		return m_vecKey[(int)_eKey].eState;
	}

	Vec2 GetMousePos()
	{
		return m_vCurMousePos;
	}
};

