#pragma once
#include "CObject.h"
#include "CTexture.h"

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    //TODO:

public:
    CPlayer();
    ~CPlayer();
};

