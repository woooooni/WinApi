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
	//현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	//초당 카운트 횟수(1초당 몇번 셀 수 있는지)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//1. 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구하고, 초당 카운트 횟수를 나눈다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	

	//2. 이전 카운트 값을 현재 카운트 값으로 갱신한다.
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_Acc += m_dDT; // DT누적.(흐른 시간을 의미)

	//3. 흐른 시간(누적시간)이 1이 넘으면 1초가 경과.
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
