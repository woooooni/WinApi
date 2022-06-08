#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	//윈도우의 주소 경로는 255자로 제한되어 있음
	wchar_t		m_szContentPath[255];

public:
	void Init();
	wchar_t* GetContentPath() { return m_szContentPath; };

};

