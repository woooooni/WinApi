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
    void SetDir(float _fTheta)
    {
        m_fTheta = _fTheta;
    }

    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CProjectile);

public:
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    CProjectile();
    virtual ~CProjectile();
};

