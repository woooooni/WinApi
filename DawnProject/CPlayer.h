#pragma once
#include "CObject.h"
#include "CTexture.h"

class CPlayer :
    public CObject
{
private:
    vector<CObject*>    m_vecColObj;
    PLAYER_STATE        m_ePrevState;
    PLAYER_STATE        m_eCurState;
    int                 m_iDir;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateProjectile();
    void update_state();
    void update_move();
    void update_animation();

    CLONE(CPlayer);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    CPlayer();
    ~CPlayer();
};

