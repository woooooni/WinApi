#pragma once


class CRes
{
private:
	wstring m_strkey;	// ���ҽ� Ű��
	wstring m_strRelativePath;		// ���ҽ� "���"���

public:
	void SetKey(wstring _strkey) { m_strkey = _strkey; }
	void SetRelativePath(wstring _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const wstring& GetKey() { return m_strkey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();

};

