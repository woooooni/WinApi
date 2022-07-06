#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//m_arrObj[i] �׷� ������ j ��ü ����.
			delete m_arrObj[i][j];
		}
	}
}


void CScene::SetName(const wstring& _strName)
{
	m_strName = _strName;
}

const wstring& CScene::GetName()
{
	return m_strName;
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) 
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//#include "func.h"
	//Template Func
	//�Լ��� �ƴ�. => �����Ϸ��� ��û�� Ÿ�Կ� ���� �Լ��� "����"�ؼ� ȣ���ϴ� ����.
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	CTexture* pTileTexture = CResMgr::GetInst()->LoadTexture(L"TileSet", L"texture\\tile\\tileset.bmp");
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	//Ÿ�� ����.
	for (UINT i = 0; i < _iXCount; i++)
	{
		for (UINT j = 0; j < _iYCount; j++)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTexture);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}
