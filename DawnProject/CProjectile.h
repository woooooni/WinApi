#pragma once
#include "CObject.h"
class CProjectile :
    public CObject
{
private:
    float   m_fTheta;
    float   m_fSpeed;
    Vec2    m_vDir;

public:
    void SetDir(float _fTheta);
    void SetDir(Vec2 _vDir);

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    CProjectile();
    virtual ~CProjectile();
};

