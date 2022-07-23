#include "pch.h"
#include "CComponent.h"
#include "CAnimator.h"
#include "CAnimation.h"


CAnimator::CAnimator()
	:m_pCurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, 
										Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, 
										float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);
	
	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	//pAnim->Load(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator::update()
{

		


}

void CAnimator::finalupdate()
{
	//�ִϸ����� �帧
	// =========================				
	//		Object->update()
	// ========================
	// �浹, �̵� ���� ������Ʈ�� ȣ��.
	// 
	// ========================
	//		Animator->update()
	// ========================
	//���� �ִϸ��̼��� ������Ʈ�� ȣ��.
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();

		// C++ �ڵ�����ȭ
		// && ���꿡��, �պκ� ������ false��� �� �κ� ������ �˻����� ����.
		// || ���꿡��, �պκ� ������ true��� �� �κ� ������ �˻����� ����.
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}
