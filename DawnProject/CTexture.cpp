#include "pch.h"
#include "CCore.h"
#include "CTexture.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{

}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDc());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit =(HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInst()->GetMainDc();

	m_hBit = CreateCompatibleBitmap(mainDC, (int)_iWidth, (int)_iHeight);
	m_dc = CreateCompatibleDC(mainDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
