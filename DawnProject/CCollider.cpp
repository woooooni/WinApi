#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextId = 0;

CCollider::CCollider()
	:m_pOwner(nullptr)
	,m_iId(g_iNextId++) //Collider 생성 시 마다 static 멤버인 아이디가 하나씩 증가하고 "고유한"아이디 값을 가짐.
	,ePenType(PEN_TYPE::GREEN)
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


