#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr() 
	:m_arrCheck{}
{	
}

CCollisionMgr::~CCollisionMgr() 
{
}

void CCollisionMgr::init()
{

}

void CCollisionMgr::update()
{
	
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++) 
	{
		
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}


//TODO::�ݶ��̴� ������Ʈ ���� ����
void CCollisionMgr::CollisionUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObejct(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObejct(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			//no has collider
			continue;
		}
			

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
			{
				//no has collider or same object
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// gen map key by using union
			// �� Collider ���� ���̵� ����.
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetId();
			ID.iRight_id = pRightCol->GetId();
			
			//���� ������ �浹���� ��������.
			 iter = m_mapColInfo.find(ID.ID);

			//�浹 ������ ��ϵ��� ������� ���.
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}
			
			if (IsCollision(pLeftCol, pRightCol))
			{
				//���� �浹 ���� ���
				if (iter->second)
				{
					//���� �����ӿ��� �浹 ���̾��� ���.
					//�� �� �ϳ��� ���� ������ ���. �������������� ���
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					//���� �����ӿ� �浹 ������ �ʾ���. => �浹 Ʈ���� ȣ��.
					//�� �� �ϳ��� ���� ������ ���, �浹���� ���� ������ ���.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				//���� �浹 ���� �ƴҰ��
				if (iter->second)
				{
					//���� �����ӿ��� �浹 ���̾��� ���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
			
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// TODO::�浹 �˻� ���� ����
	// 1. �浹ü�� ũ�������� ������ ����.
	// 2. ���� ������ �� �浹������ �ϸ� ��. => ������ ��ǥ�� ������ �̿��� ��ġ���� üũ�ϸ��.
	// 3. ���� : x, y, scaleX, scaleY
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if ((abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f) &&
		(abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f))
	{
		return true;
	}

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//_eLeft, _eRight �� �� ���� ���� ������ ��ƾ� ��.
	//ū ���� ��(��Ʈ)�� ��ƾ� ��.
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow) 
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) //TODO::
	{
		m_arrCheck[iRow] &= ~( 1 << iCol);
	}
	else 
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}


