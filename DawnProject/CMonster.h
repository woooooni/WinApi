#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
<<<<<<< HEAD
=======

public:
    CMonster();
    ~CMonster();
>>>>>>> 2d11748a2eab7f4333a0aab5d3d8f79b3c8bc5e5
public:
    virtual void update();
    virtual void render(HDC _dc);
};

