#include "pch.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "AI.h"
#include "CTexture.h"
#include "CObject.h"
#include "CMonster.h"

CMonster::CMonster()
	:m_tInfo{}
{
	//Texture로딩
	m_pTex = CResMgr::GetInst()->
		LoadTexture(L"Monster", L"texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

}
CMonster::~CMonster() 
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	if(nullptr != m_pAI)
		m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	Vec2 _vecScale = GetScale();
	Vec2 _vecPos = GetPos();

	//unsigned int시, 음수로 넘어가면 상위비트가 1로 변경되어 매우 큰 값이 세팅됨.
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	_vecPos = CCamera::GetInst()->GetRenderPos(_vecPos);

	TransparentBlt(_dc
		, (int)(_vecPos.x - (float)(iWidth / 2))
		, (int)(_vecPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}
