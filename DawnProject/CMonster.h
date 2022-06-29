#pragma once
#include "CObject.h"
#include "CTexture.h"

class CMonster :
    public CObject
{

private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:

public:
    CMonster();
    ~CMonster();
};

