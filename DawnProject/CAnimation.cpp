#include "pch.h"
#include "CCore.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)
	, m_fAccTime(0)

{

}

CAnimation::~CAnimation()
{
}



void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += DeltaTimef;

	//1. �ݺ� ����
	//2. ���� �ð� ����.
	//3. �� ���� => DeltaTime�� ���� ���� ���.
	if (m_vecFrame[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrame.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0;
			return;
		}

		m_fAccTime -= m_vecFrame[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;


	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	
	//TODO::����
	//TransparentBlt()�� Destination x,y ��ġ�� (�÷��̾��� ���� ������ - �����̽� ������ ���ݸ�ŭ ������ ������)��.

	//Object Position�� Offset��ŭ �̵�.
	vPos += m_vecFrame[m_iCurFrm].vOffset;

	//ī�޶��� ��ġ�� ���� ������ ��ǥ�� ��ȯ.
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	draw(_dc, vPos);
	
}

void CAnimation::Create(CTexture* _pTex, 
							Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, 
							float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frm = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrame.push_back(frm);
	}
}

void CAnimation::draw(HDC _dc, Vec2 _vRenderPos)
{
	TransparentBlt(_dc
		, (int)(_vRenderPos.x - m_vecFrame[m_iCurFrm].vSlice.x / 2.f)
		, (int)(_vRenderPos.y - m_vecFrame[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrame[m_iCurFrm].vLT.x)
		, (int)(m_vecFrame[m_iCurFrm].vLT.y)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255));
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);
	
	// Animation �̸� ����.
	// TODO::���� ����ϹǷ�, �Լ�ȭ �ϴ°��� ���ƺ���.
	// TODO::Serialization ����.
	fprintf(pFile, "[Animation Name] ");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	// �ؽ��� ����
	// �ؽ��� Ű��
	fprintf(pFile, "[Texture Name] ");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");


	// �ؽ��� ��� ��� ����
	fprintf(pFile, "[Texture Path] ");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");


	//Animation ��� ������ ����.(vector)
	//������ ����
	fprintf(pFile, "[Frame Count] ");
	fprintf(pFile, "%d\n", (int)m_vecFrame.size());

	//
	for (size_t i = 0; i < m_vecFrame.size(); i++)
	{
		fprintf(pFile, "[Frame Index] ");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Slice Size] ");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrame[i].vSlice.x, (int)m_vecFrame[i].vSlice.y);

		fprintf(pFile, "[Offset] ");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrame[i].vOffset.x, (int)m_vecFrame[i].vOffset.y);

		fprintf(pFile, "[Duration] ");
		fprintf(pFile, "%d\n", (int)m_vecFrame[i].fDuration);

		fprintf(pFile, "[Left Top] ");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrame[i].vLT.x, (int)m_vecFrame[i].vLT.y);

		fprintf(pFile, "\n");
		
	}
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	//�ִϸ��̼� �̸�
	LoadWString(m_strName, pFile);
	
	//�ؽ���
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	//������ ����
	size_t iFrameCount = m_vecFrame.size();
	fread(&iFrameCount, sizeof(tAnimFrame), 1, pFile);

	//��� ������ ����
	m_vecFrame.resize(iFrameCount);
	fread(m_vecFrame.data(), sizeof(tAnimFrame), iFrameCount, pFile);


	fclose(pFile);
}

