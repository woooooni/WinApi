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
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	//Texture로딩
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 416.f), Vec2(96.f, 104.f), Vec2(96.f, 0.f), .1f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	//for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	//{
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -100.f);
	//}
	
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	/*Vec2 _vecPos = GetPos();
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
	}*/

	if (KEY_TAP(KEY::SPACE))
	{
		CreateProjectile();
	}

	/*SetPos(_vecPos);*/
	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{

	
	/*
	* 텍스처 "직접"로딩해 사용시 아래 코드 사용.
	* ===================================================================
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
	* ===================================================================
	*/
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Mushroom", L"texture\\Player_A.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	float width = pTex->Width();
	float height = pTex->Height();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;
	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, (int)width, (int)height
		, pTex->GetDC()
		, 0, 0
		, (int)width, (int)height
		, bf);
	// 컴포넌트(충돌체, etc..)가 있는 경우 렌더
	//component_render(_dc);
}

void CPlayer::CreateProjectile()
{
	CProjectile* projectile = new CProjectile;
	projectile->SetPos(GetPos());
	projectile->SetScale(Vec2(20, 20));
	projectile->SetDir(Vec2(1, 0));
	projectile->SetName(L"PLAYER_PROJECTILE");

	//#include "func.h"
	CreateObj(projectile, GROUP_TYPE::PLAYER_PROJECTILE);


	//이벤트 매니저가 처리
	/*CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
	pCurScene->AddObject(projectile, GROUP_TYPE::PLAYER);*/
}
