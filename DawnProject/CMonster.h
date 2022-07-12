#pragma once

class CTexture;
class AI;


class CMonster :
    public CObject
{

private:
    CTexture*   m_pTex;
    AI*         m_pAI;

public:
    void SetAI(AI* _pAI) { m_pAI = _pAI; m_pAI->m_pOwner = this; }

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CMonster);
private:

public:
    CMonster();
    ~CMonster();
};

