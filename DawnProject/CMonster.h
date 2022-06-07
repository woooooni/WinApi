#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
public:
    virtual void update();
    virtual void render(HDC _dc);
};

