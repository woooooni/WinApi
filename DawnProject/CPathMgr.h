#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	//�������� �ּ� ��δ� 255�ڷ� ���ѵǾ� ����
	wchar_t		m_szContentPath[255];
	wchar_t		m_szRelativePath[256];
public:
	void Init();
	wchar_t* GetContentPath() { return m_szContentPath; };

	wstring GetRelativePath(const wchar_t* _filePath);
};

