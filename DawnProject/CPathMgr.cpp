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
	

	//!����
	// VisualStudio��� ������ ����� �����߱� ������ ��������� ���� ��, ������Ʈ �̸����� ����.
	// ���� �� �����ϴ� ��δ� �ٸ�.
	int iLen = (int)wcslen(m_szContentPath);

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

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = _filePath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen- iAbsLen);
	return strRelativePath;
}
