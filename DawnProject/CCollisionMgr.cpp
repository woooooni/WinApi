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


//TODO::콜라이더 업데이트 로직 공부
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
			// 두 Collider 조합 아이디 생성.
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetId();
			ID.iRight_id = pRightCol->GetId();
			
			//이전 프레임 충돌정보 가져오기.
			 iter = m_mapColInfo.find(ID.ID);

			//충돌 정보가 등록되지 않은경우 등록.
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}
			
			if (IsCollision(pLeftCol, pRightCol))
			{
				//현재 충돌 중일 경우
				if (iter->second)
				{
					//이전 프레임에도 충돌 중이었을 경우.
					//둘 중 하나가 삭제 예정일 경우. 빠져나간것으로 취급
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
					//이전 프레임에 충돌 중이지 않았음. => 충돌 트리거 호출.
					//둘 중 하나가 삭제 예정일 경우, 충돌하지 않은 것으로 취급.
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
				//현재 충돌 중이 아닐경우
				if (iter->second)
				{
					//이전 프레임에도 충돌 중이었을 경우.
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
	// TODO::충돌 검사 로직 공부
	// 1. 충돌체는 크기정보를 가지고 있음.
	// 2. 서로 겹쳤을 때 충돌판정을 하면 됨. => 각각의 좌표와 범위를 이용해 겹치는지 체크하면됨.
	// 3. 공식 : x, y, scaleX, scaleY
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
	//_eLeft, _eRight 중 더 작은 수를 행으로 잡아야 함.
	//큰 값을 열(비트)로 잡아야 함.
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


