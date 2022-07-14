#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextId = 0;


CCollider::CCollider()
	:m_pOwner(nullptr)
	, m_iId(g_iNextId++) //Collider 생성 시 마다 static 멤버인 아이디가 하나씩 증가하고 "고유한"아이디 값을 가짐.
	, ePenType(PEN_TYPE::GREEN)
	, m_bTrigger(false)
	, m_bActive(true)
{

}

CCollider::~CCollider()
{

}

//복사 생성자 정의
CCollider::CCollider(const CCollider& _origin)// Object와 Collider는 종속관계. 복사시에 다른 오브젝트일 수도 있음.
	:m_pOwner(nullptr) 
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iId(g_iNextId++)
	, ePenType(PEN_TYPE::GREEN)
	, m_bTrigger(_origin.m_bTrigger)
	, m_bActive(_origin.m_bActive)
{
	
}

void CCollider::finalupdate()
{
	//Object Follow
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	SelectGDI p(_dc, ePenType);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	//오브젝트의 크기만큼 빈 박스를 그림.
	Rectangle(_dc,
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f),
		(int)(vRenderPos.y + m_vScale.y / 2.f));
	
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
	HDC _dc = CCore::GetInst()->GetMainDc();

	ePenType = PEN_TYPE::BLUE;
	SetTextColor(_dc, RGB(0, 0, 0));
	TextOut(_dc, 5, 5, L"OnCollision", lstrlen(L"OnCollision"));

	//PushOutInterSection(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);

	this->ePenType = PEN_TYPE::RED;
	HDC _dc = CCore::GetInst()->GetMainDc();

	SetTextColor(_dc, RGB(0, 0, 0));
	TextOut(_dc, 5, 5, L"OnCollisionEnter", lstrlen(L"OnCollisionEnter"));
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
	this->ePenType = PEN_TYPE::GREEN;

	HDC _dc = CCore::GetInst()->GetMainDc();
	SetTextColor(_dc, RGB(0, 0, 0));
	TextOut(_dc, 5, 5, L"OnCollisionExit", lstrlen(L"OnCollisionExit"));
}




void CCollider::PushOutInterSection(CCollider* _pOther)
{
	HDC _dc = CCore::GetInst()->GetMainDc();

	SelectGDI p(_dc, PEN_TYPE::RED);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	

	//if ((abs(vOtherPos.x - vPos.x) < (vScale.x + vOtherScale.x) / 2.f) &&
	//	(abs(vOtherPos.y - vPos.y) < (vScale.y + vOtherScale.y) / 2.f))
	//{
	//	return true;
	//}

	RECT rect = GetInterSection(_pOther);
	if (rect.top == 0 && rect.left == 0 && rect.right == 0 && rect.bottom == 0)
		return;

	Rectangle(_dc
		, rect.left
		, rect.top
		, rect.left + rect.right
		, rect.top + rect.bottom);

	//Vec2 vDir = Vec2((float)rect.left + rect.right, (float)rect.top + rect.bottom);
	//vDir.Normalize();

	//int iDiffX = rect.left - (rect.left + rect.right);
	//int iDiffY = rect.top - (rect.top + rect.bottom);
	//
	//GetObj()->GetRigidBody()->AddForce(-vDir * (iDiffX + iDiffY));
}


RECT CCollider::GetInterSection(CCollider* _pOther)
{
	RECT rect = {};

	Vec2 vPos = GetObj()->GetPos();
	Vec2 vScale = GetObj()->GetScale();

	Vec2 vOtherPos = _pOther->GetFinalPos();
	Vec2 vOtherScale = _pOther->GetScale();

	Vec2 iR1Left = vPos - (vScale / 2.f);
	Vec2 iR2Left = vOtherPos - (vOtherScale / 2.f);

	if ((iR1Left.x > iR2Left.x + vOtherScale.x) || (iR1Left.x + vScale.x < iR2Left.x)
		|| (iR1Left.y > iR2Left.y + vOtherScale.y) || (iR1Left.y + vScale.y < iR2Left.y))
		return rect;

	rect.left = max(iR1Left.x, iR2Left.x);
	rect.top = max(iR1Left.y, iR2Left.y);
	rect.right = min(iR1Left.x + vScale.x, iR2Left.x + vOtherScale.x) - rect.left;
	rect.bottom = min(iR1Left.y + vScale.y, iR2Left.y + vOtherScale.y) - rect.top;

	return rect;
}

