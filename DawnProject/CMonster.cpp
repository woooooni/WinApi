#include "pch.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "AI.h"
#include "CTexture.h"
#include "CObject.h"
#include "CMonster.h"

CMonster::CMonster() 
{
	//Texture�ε�
	m_pTex = CResMgr::GetInst()->
		LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

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
	m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	Vec2 _vecScale = GetScale();
	Vec2 _vecPos = GetPos();

	//unsigned int��, ������ �Ѿ�� ������Ʈ�� 1�� ����Ǿ� �ſ� ū ���� ���õ�.
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 Vec2 = GetPos();

	TransparentBlt(_dc
		, (int)(_vecPos.x - (float)(iWidth / 2))
		, (int)(_vecPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}
