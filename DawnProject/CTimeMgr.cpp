#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_Acc(0)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	//�ʴ� ī��Ʈ Ƚ��(1�ʴ� ��� �� �� �ִ���)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//1. ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���ϰ�, �ʴ� ī��Ʈ Ƚ���� ������.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	

	//2. ���� ī��Ʈ ���� ���� ī��Ʈ ������ �����Ѵ�.
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_Acc += m_dDT; // DT����.(�帥 �ð��� �ǹ�)

	//3. �帥 �ð�(�����ð�)�� 1�� ������ 1�ʰ� ���.
	if (m_Acc >= 1.) 
	{
		m_iFPS = m_iCallCount;
		m_Acc = 0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);

		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
