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

	//1. 반복 문제
	//2. 남은 시간 문제.
	//3. 렉 문제 => DeltaTime이 높게 잡힐 경우.
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

	
	//TODO::공부
	//TransparentBlt()의 Destination x,y 위치는 (플레이어의 현재 포지션 - 슬라이스 사이즈 절반만큼 움직인 사이즈)임.

	//Object Position에 Offset만큼 이동.
	vPos += m_vecFrame[m_iCurFrm].vOffset;

	//카메라의 위치에 따른 렌더링 좌표로 전환.
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
	
	// Animation 이름 저장.
	// TODO::자주 사용하므로, 함수화 하는것이 좋아보임.
	// TODO::Serialization 공부.
	fprintf(pFile, "[Animation Name] ");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	// 텍스쳐 저장
	// 텍스쳐 키값
	fprintf(pFile, "[Texture Name] ");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");


	// 텍스쳐 상대 경로 저장
	fprintf(pFile, "[Texture Path] ");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");


	//Animation 모든 프레임 저장.(vector)
	//프레임 갯수
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

	//애니메이션 이름
	LoadWString(m_strName, pFile);
	
	//텍스쳐
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	//프레임 갯수
	size_t iFrameCount = m_vecFrame.size();
	fread(&iFrameCount, sizeof(tAnimFrame), 1, pFile);

	//모든 프레임 정보
	m_vecFrame.resize(iFrameCount);
	fread(m_vecFrame.data(), sizeof(tAnimFrame), iFrameCount, pFile);


	fclose(pFile);
}

