#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llPrevCount;


	double			m_dDT;			// 프레임 간의 시간값.
	double			m_Acc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 횟수 체크
	UINT			m_iFPS;			//

	//FPS
	//1 프레임당 시간(Delta Time)
	
public:
	void Init();
	void update();

public:
	double GetDT() { return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};

