#include "pch.h"
#include "CScene_Start.h"
#include "CCore.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	CScene::update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeSceneEvt(SCENE_TYPE::TOOL);
	}
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}
}

void CScene_Start::Enter()
{
	//Object 추가
	//Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(640, 384));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	//TODO::반복될 일이 많으므로, 전역함수로 따로 만들기
	AI* pAI = new AI;
	pAI->AddState(new CIdleState);
	pAI->AddState(new CTraceState);

	//Monster
	CMonster* pEnemy = new CMonster;
	pEnemy->SetPos(Vec2(800, 384));
	pEnemy->SetScale(Vec2(100.f, 100.f));
	pEnemy->SetName(L"Monster");

	pEnemy->SetAI(pAI);
	AddObject(pEnemy, GROUP_TYPE::MONSTER);


	// 충돌지점
	// Player 그룹과 Monster, Projectile간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER_PROJECTILE);

	//CameraLook 지정
	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	//Camera효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}

