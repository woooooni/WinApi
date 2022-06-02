#pragma once
#include "CObject.h"
class CProjectile :
    public CObject
{
public:
    CProjectile();
    ~CProjectile();

public:
    virtual void update();
    virtual void render(HDC _dc);
};

