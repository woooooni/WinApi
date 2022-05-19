#include "pch.h"
#include "CKeyMgr.h"


int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'q','w','e','r','t','y','u','i','o','p',
	'a','s','d','f','g','h','j','k','l',
	'z','x','c','v','b','n','m',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
};



CKeyMgr::CKeyMgr() 
{

}

CKeyMgr::~CKeyMgr() 
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) 
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update() 
{
	for (int i = 0; i < (int)KEY::LAST; ++i) 
	{
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) 
		{
			if (m_vecKey[i].bPrevPushed) 
				m_vecKey[i].eState = KEY_STATE::HOLD;
			else
				m_vecKey[i].eState = KEY_STATE::TAP;

			m_vecKey[i].bPrevPushed = true;
		}
		else 
		{
			if (m_vecKey[i].bPrevPushed) 
				m_vecKey[i].eState = KEY_STATE::AWAY;
			else 
				m_vecKey[i].eState = KEY_STATE::NONE;

			m_vecKey[i].bPrevPushed = false;
		}
	}
}
