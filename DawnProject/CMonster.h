#pragma once
#include "CObject.h"
#include "AI.h"
class CTexture;

struct tMonsterInfo
{
    float fSpeed;       //  �ӵ�
    float fHP;          //  ü��
    float fRecogRange;  //  ��������
    float fAttRange;    //  ���ݹ���
    float fAtt;         //  ���ݷ�
    float fDef;         //  ����
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

