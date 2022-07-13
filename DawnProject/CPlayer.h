#pragma once
#include "CObject.h"
#include "CTexture.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    ALERT,
    PRONE,
    ROPE,
    LADDER,
};


class CPlayer :
    public CObject
{
private:
    vector<CObject*>    m_vecColObj;
    PLAYER_STATE        m_eCurState;
    int                 m_iDir;
public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateProjectile();
    void update_state();

    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

