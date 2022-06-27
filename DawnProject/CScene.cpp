#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//m_arrObj[i] 그룹 벡터의 j 물체 삭제.
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
