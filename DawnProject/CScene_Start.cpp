#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CGround.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"

#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"

#include "CMonsterFactory.h"
#include "SelectGDI.h"

CScene_Start::CScene_Start()
	: m_vForcePos{}
	, m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)

{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObejct((GROUP_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && (vecObj[j]->GetRigidBody() != nullptr))
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize()* fForce);
					}
				}
				vecObj[j]->update();
			}
		}
	}

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

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);
	if (!m_bUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);
	m_fCurRadius += m_fForceRadius * 2.f * DeltaTimef;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(
		_dc
		, vRenderPos.x - m_fCurRadius
		, vRenderPos.y - m_fCurRadius
		, vRenderPos.x + m_fCurRadius
		, vRenderPos.y + m_fCurRadius);
	
}

void CScene_Start::Enter()
{
	//Object 추가
	//Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(640.f, 384.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	pPlayer->SetType(GROUP_TYPE::PLAYER);
	AddObject(pPlayer, GROUP_TYPE::PLAYER);
	RegisterPlayer(pPlayer);

	//TODO::반복될 일이 많으므로, 전역함수로 따로 만들기(CMonsterFactory)
	CMonster* pMon = CMonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, Vec2(940, 384));
	AddObject(pMon, GROUP_TYPE::MONSTER);


	// 땅 배치
	CGround* pGround = new CGround;
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(200.f, 60.f));
	pGround->SetType(GROUP_TYPE::GROUND);
	AddObject(pGround, GROUP_TYPE::GROUND);

	// 충돌지점
	// 그룹간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);

	//CameraLook 지정
	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	//Camera효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	init();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

}

