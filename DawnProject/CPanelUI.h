#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;
public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();

    
public:
    CPanelUI();
    ~CPanelUI();
    CLONE(CPanelUI);
};

