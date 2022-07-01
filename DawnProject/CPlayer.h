#pragma once
#include "CObject.h"
#include "CTexture.h"

class CPlayer :
    public CObject
{
private:


public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateProjectile();

    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

