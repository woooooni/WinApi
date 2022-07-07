#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"

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
	//타일생성
	CreateTile(5, 5);

	//Camera Look 지정.
	Vec2 vResolution = CCore::GetInst()->GetResoultionVec();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	//Template UI
	CUI* pUI = new CUI(false);
	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2((vResolution.x - pUI->GetScale().x), 0.f));

	CUI* pChildUI = new CUI(false);
	pChildUI->SetScale(Vec2(100.f, 40.f));
	pChildUI->SetPos(Vec2(0.f, 0.f));

	pUI->AddChild(pChildUI);
	AddObject(pUI, GROUP_TYPE::UI);

}

void CScene_Tool::Exit()
{

}

void CScene_Tool::SetTileIndex()
{
	Vec2 vMousePos = MOUSE_POS;
	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

	int iTileX = (int)GetTileX();
	int iTileY = (int)GetTileY();

	int iCol = (int)vMousePos.x / TILE_SIZE;
	int iRow = (int)vMousePos.y / TILE_SIZE;

	if (iCol < 0.f || iTileX <= iCol || iRow < 0.f || iTileY <= iRow)
		return;

	UINT iIdx = iRow * iTileX + iCol;

	const vector<CObject*>& vecTile = GetGroupObejct(GROUP_TYPE::TILE);
	((CTile*)vecTile[iIdx])->AddImgIdx();
}

void CScene_Tool::update()
{
	CScene::update();
	if (KEY_TAP(KEY::LBTN))
	{
		SetTileIndex();
	}
}









/*
* ================================================
* TILE COUNT Window Proc
* ================================================
*/

//★해당 cpp의 멤버함수가 "절대"아니니까 착각하지 말자.
INT_PTR _stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_XCOUNT, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_YCOUNT, nullptr, false);
			
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();
			
			//TODO::dynamic_cast 공부
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);


			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

