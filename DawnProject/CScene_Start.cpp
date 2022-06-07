#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{
	//Object �߰�
	CPlayer* pPlayer = new CPlayer;
	CMonster* pMonster = new CMonster;
	

	pPlayer->SetPos(Vec2(640, 384));
	pPlayer->SetScale(Vec2(100.f, 100.f));

	AddObject(pPlayer, GROUP_TYPE::DEFAULT);

}

void CScene_Start::Exit()
{
}

