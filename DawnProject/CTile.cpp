#include "CTile.h"

CTile::CTile()
	:m_pTileTexture(nullptr)
	, m_iIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{

}


void CTile::update()
{

}

void CTile::render(HDC _dc)
{
	if (m_pTileTexture == nullptr || m_iIdx == -1)
		return;

	UINT iWidth = m_pTileTexture->Width();
	UINT iHeight = m_pTileTexture->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = m_iIdx / iMaxCol;
	UINT iCurCol = m_iIdx % iMaxCol;

	// 이미지 범위를 벗어난 인덱스
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(
		_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, m_pTileTexture->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}

