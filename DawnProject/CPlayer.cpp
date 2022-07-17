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
#include "CRigidBody.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
{

	//Collider
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, -10.f));
	GetCollider()->SetScale(Vec2(60.f, 80.f));

	//RigidBody
	CreateRigidBody();
	GetRigidBody()->SetGravity(true);

	//Animator
	//Texture로딩
	CTexture* pTexIdle = CResMgr::GetInst()->LoadTexture(L"Player_Idle", L"texture\\Player\\Idle.bmp");
	CTexture* pTexAlert = CResMgr::GetInst()->LoadTexture(L"Player_Alert", L"texture\\Player\\Alert.bmp");
	CTexture* pTexWalk = CResMgr::GetInst()->LoadTexture(L"Player_Walk", L"texture\\Player\\Walk.bmp");
	CTexture* pTexJump = CResMgr::GetInst()->LoadTexture(L"Player_Jump", L"texture\\Player\\Jump.bmp");
	CTexture* pTexDead = CResMgr::GetInst()->LoadTexture(L"Player_Dead", L"texture\\Player\\Dead.bmp");
	CTexture* pTexProne = CResMgr::GetInst()->LoadTexture(L"Player_Prone", L"texture\\Player\\Prone.bmp");

	
	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player\\idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\player\\alert.anim");
	GetAnimator()->LoadAnimation(L"animation\\player\\walk.anim");
	GetAnimator()->LoadAnimation(L"animation\\player\\jump.anim");
	GetAnimator()->LoadAnimation(L"animation\\player\\dead.anim");
	GetAnimator()->LoadAnimation(L"animation\\player\\prone.anim");

	
	/*GetAnimator()->CreateAnimation(L"IDLE", pTexIdle, Vec2(0.f, 0.f), Vec2(pTexIdle->Width() / 3, (float)pTexIdle->Height()), Vec2(pTexIdle->Width() / 3, 0.f), .5f, 3);
	GetAnimator()->CreateAnimation(L"ALERT", pTexAlert, Vec2(0.f, 0.f), Vec2(pTexAlert->Width() / 3, (float)pTexAlert->Height()), Vec2(pTexAlert->Width() / 3, 0.f), .1f, 3);
	GetAnimator()->CreateAnimation(L"WALK", pTexWalk, Vec2(0.f, 0.f), Vec2(pTexWalk->Width() / 4, (float)pTexWalk->Height()), Vec2(pTexWalk->Width() / 4, 0.f), .1f, 4);
	GetAnimator()->CreateAnimation(L"JUMP", pTexJump, Vec2(0.f, 0.f), Vec2(pTexJump->Width(), (float)pTexJump->Height()), Vec2(0.f, 0.f), .1f, 1);
	GetAnimator()->CreateAnimation(L"DEAD", pTexDead, Vec2(0.f, 0.f), Vec2(pTexDead->Width(), (float)pTexDead->Height()), Vec2(0.f, 0.f), .1f, 1);
	GetAnimator()->CreateAnimation(L"PRONE", pTexProne, Vec2(0.f, 0.f), Vec2(pTexProne->Width(),(float)pTexProne->Height()), Vec2(0.f, 0.f), .1f, 1);

	GetAnimator()->FindAnimation(L"IDLE")->Save(L"animation\\player\\idle.anim");
	GetAnimator()->FindAnimation(L"ALERT")->Save(L"animation\\player\\alert.anim");
	GetAnimator()->FindAnimation(L"WALK")->Save(L"animation\\player\\walk.anim");
	GetAnimator()->FindAnimation(L"JUMP")->Save(L"animation\\player\\jump.anim");
	GetAnimator()->FindAnimation(L"DEAD")->Save(L"animation\\player\\dead.anim");
	GetAnimator()->FindAnimation(L"PRONE")->Save(L"animation\\player\\prone.anim");*/
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	//for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, 0.f);
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	
	update_move();
	update_state();
	update_animation();

	GetAnimator()->update();
	m_ePrevState = m_eCurState;
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
	/* ===================================================================
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Mushroom", L"texture\\Player_A.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);
	//float width = pTex->Width();
	//float height = pTex->Height();

	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127;
	//AlphaBlend(_dc
	//	, int(vPos.x - width / 2.f)
	//	, int(vPos.y - height / 2.f)
	//	, (int)width, (int)height
	//	, pTex->GetDC()
	//	, 0, 0
	//	, (int)width, (int)height
	//	, bf);
	*/
	component_render(_dc);
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

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::LEFT))
	{
		m_iDir = -1;
		GetAnimator()->SetFlipX(false);
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		m_iDir = 1;
		GetAnimator()->SetFlipX(true);
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_HOLD(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;
	}

	if (0.f >= GetRigidBody()->GetSpeed())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();
	if (KEY_HOLD(KEY::LEFT))
	{
		pRigid->AddForce(Vec2(-100.f, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		pRigid->AddForce(Vec2(100.f, 0.f));
	}

	//KEY_TAP
	if (KEY_TAP(KEY::LEFT))
	{
		pRigid->AddVelocity(Vec2(-200.f, 0.f));
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		pRigid->AddVelocity(Vec2(200.f, 0.f));
	}
	if (KEY_TAP(KEY::SPACE))
	{
		pRigid->SetGround(false);
		pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, -400.f));
	}

	//KEY AWAY
	if (KEY_AWAY(KEY::LEFT))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
	if (KEY_AWAY(KEY::RIGHT))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}
	//if (KEY_TAP(KEY::SPACE))
	//{
	//	CreateProjectile();
	//}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		GetAnimator()->Play(L"IDLE", true);
		break;
	case PLAYER_STATE::ALERT:
		break;
	case PLAYER_STATE::JUMP:
		GetAnimator()->Play(L"JUMP", true);
		break;
	case PLAYER_STATE::LADDER:
		break;
	case PLAYER_STATE::ROPE:
		break;
	case PLAYER_STATE::PRONE:
		break;
	case PLAYER_STATE::WALK:
		GetAnimator()->Play(L"WALK", true);
		break;
	case PLAYER_STATE::ATTACK:
		break;
	}
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetType() == GROUP_TYPE::GROUND)
	{
		CRigidBody* rigid = GetRigidBody();
		if (rigid == nullptr)
			return;

		rigid->SetGround(true);
	}
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetType() == GROUP_TYPE::GROUND)
	{
		CRigidBody* rigid = GetRigidBody();
		if (rigid == nullptr)
			return;

		rigid->SetGround(true);
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetType() == GROUP_TYPE::GROUND)
	{
		CRigidBody* rigid = GetRigidBody();
		if (rigid == nullptr)
			return;

		rigid->SetGround(false);
	}
}
