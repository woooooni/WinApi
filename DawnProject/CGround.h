#pragma once
#include "CObject.h"

class CCollider;

class CGround :
    public CObject
{

private:
    virtual void init();
    virtual void update();

public:
    CLONE(CGround);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    
public:
    CGround();
    ~CGround();
};

