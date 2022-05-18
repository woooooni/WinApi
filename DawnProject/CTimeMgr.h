#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llPrevCount;


	double			m_dDT;			// ������ ���� �ð���.
	double			m_Acc;			// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS;			//

	//FPS
	//1 �����Ӵ� �ð�(Delta Time)
	
public:
	void Init();
	void update();

public:
	double GetDT() { return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};

