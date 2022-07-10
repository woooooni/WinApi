#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CUIMgr.h"
/* Tool Scene 
* 
* 
*/
void ChangeScene(DWORD_PTR, DWORD_PTR);
CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)
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
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2((vResolution.x - pPanelUI->GetScale().x), 0.f));

	CButtonUI* pBtnUI = new CButtonUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pBtnUI->SetClickedCallBack(this, ((SCENE_MEMFUNC)&CScene_Tool::SaveTileData));
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);


	/*CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-200.f, 0.f));
	((CButtonUI*)pClonePanel->GetChildrenUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);

	AddObject(pClonePanel, GROUP_TYPE::UI);*/
}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();
	if (KEY_TAP(KEY::LBTN))
	{
		SetTileIndex();
	}
	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
	}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
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

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	//MSDN에서 예시코드를 제공.
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//  커널 오브젝트 FILE -> 프로그램과 하드디스크 사이 연결(Stream)을 잡아주는 역할.
	FILE* pFile = nullptr;

	//파일 스트림 열기
	//FILE_MODES => MSDN 참고 
	// w: write, b: binary (b 명시 안하면 자동으로 문자로 인식한다.)


	//쓰기모드에서 파일이 존재하지 않으면, 자동으로 생성.
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	assert(pFile);

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);



	const vector<CObject*>& vecTile = GetGroupObejct(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	//파일 스트림 닫기
	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	//MSDN에서 예시코드를 제공.
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeSceneEvt(SCENE_TYPE::START);
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

