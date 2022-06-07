#pragma once
#include "CObject.h"
class CProjectile :
    public CObject
{
private:
    float m_fdir;

public:
    float GetDir();
    void SetDir(float _dir);


public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    CProjectile();
    virtual ~CProjectile();
};

