#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"

/* Tool Scene 
* 
* 
*/
CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	CTexture* pTileTexture = CResMgr::GetInst()->LoadTexture(L"TileSet", L"texture\\tile\\tileset.bmp");
	wstring path = pTileTexture->GetRelativePath();


	//타일 생성.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTexture);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}

	//Camera Look 지정.
	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::update()
{
	CScene::update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeSceneEvt(SCENE_TYPE::START);
	}
}
