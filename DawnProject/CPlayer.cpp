#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CProjectile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"

CPlayer::CPlayer()
	:m_pTex()
{
	//Texture로딩
	m_pTex = CResMgr::GetInst()->
		LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	Vec2 _vecPos = GetPos();
	if (KEY_HOLD(KEY::UP))
	{
		_vecPos.y -= 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		_vecPos.x -= 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		_vecPos.y += 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		_vecPos.x += 200.f * DeltaTimef;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		//TODO
		CProjectile* projectile = new CProjectile;
		projectile->SetPos(GetPos());
		projectile->SetScale(Vec2(20, 20));
		projectile->SetDir(Vec2(1, 0));
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
		pCurScene->AddObject(projectile, GROUP_TYPE::PROJECTILE);
	}

	SetPos(_vecPos);
}

void CPlayer::render(HDC _dc)
{
	Vec2 _vecScale = GetScale();
	Vec2 _vecPos = GetPos();

	//unsigned int시, 음수로 넘어가면 상위비트가 1로 변경되어 매우 큰 값이 세팅됨.
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height(); 

	Vec2 Vec2 = GetPos();

	TransparentBlt(_dc
		, (int)_vecPos.x - (float)(iWidth / 2)
		, (int)_vecPos.y - (float)(iHeight / 2)
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		,RGB(255, 0, 255));

	/*TransparentBlt(_dc,
		(int)_vecPos.x - _vecScale.x / 2,
		(int)_vecPos.y - _vecScale.y / 2,
		(int)_vecPos.x + _vecScale.x / 2,
		(int)_vecPos.y + _vecScale.y / 2,
		);*/
}
