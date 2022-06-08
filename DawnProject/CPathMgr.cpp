#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	:m_szContentPath{0}
{
}

CPathMgr::~CPathMgr() 
{
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);
	

	//!주의
	// VisualStudio라는 도구를 사용해 빌드했기 때문에 디버깅으로 실행 시, 프로젝트 이름으로 잡힘.
	// 빌드 후 배포하는 경로는 다름.
	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}
