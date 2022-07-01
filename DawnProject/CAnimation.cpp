#include "pch.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTimeMgr.h"

CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)

{

}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += DeltaTimef;

	//1. �ݺ� ����
	//2. ���� �ð� ����.
	//3. �� ���� => DeltaTime�� ���� ���� ���.
	if (m_vecFrame[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;
		if (m_vecFrame.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			return;
		}

		m_fAccTime -= m_vecFrame[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;


	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	
	//TODO::����
	//TransparentBlt()�� Destination x,y ��ġ�� (�÷��̾��� ���� ������ - �����̽� ������ ���ݸ�ŭ ������ ������)��.
	
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrame[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrame[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrame[m_iCurFrm].vLT.x)
		, (int)(m_vecFrame[m_iCurFrm].vLT.y)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _pTex, 
							Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, 
							float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frm = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrame.push_back(frm);
	}
}

