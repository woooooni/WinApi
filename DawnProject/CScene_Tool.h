#pragma once
#include "CScene.h"
class CScene_Tool :
    public CScene
{
private:

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIndex();


public:
    CScene_Tool();
    ~CScene_Tool();
};

