#pragma once
#include "CObject.h"
#include "AI.h"
class CTexture;

struct tMonsterInfo
{
    float fSpeed;       //  속도
    float fHP;          //  체력
    float fRecogRange;  //  인지범위
    float fAttRange;    //  공격범위
    float fAtt;         //  공격력
    float fDef;         //  방어력
};

class CMonster :
    public CObject
{

private:
    tMonsterInfo    m_tInfo;
    CTexture*       m_pTex;
    AI*             m_pAI;

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _fSpeed) { m_tInfo.fSpeed = _fSpeed; }
    void SetAI(AI* _pAI) { m_pAI = _pAI; m_pAI->m_pOwner = this; }

    const tMonsterInfo& GetInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonsterInfo& _info){ m_tInfo = _info; }


public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CMonster);
private:

public:
    CMonster();
    ~CMonster();

    friend class CMonsterFactory;
};

