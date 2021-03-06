#pragma once
#include "pch.h"
#include "CObject.h"

class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;
    Vec2            m_vFinalPos;

    bool            m_bCamAffected; //  UI가 카메라에 영향을 받는지 여부.
    bool            m_bMouseOn;     //  UI 위에 마우스가 있는지 여부.
    bool            m_bLbtnDown;    //  왼쪽 버튼이 눌린적 있는지 여부.
    bool            m_bRbtnDown;    //  오른쪽 버튼이 눌린적 있는지 여부.

    wstring         m_strText;      //UI 텍스트
public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLBtnDown() { return m_bLbtnDown; }


    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>& GetChildrenUI() { return m_vecChildUI; }

    void SetText(const wstring& _strText)
    {
        m_strText = _strText;
    }

    const wstring& GetText()
    {
        return m_strText;
    }
private:
    void MouseOnCheck();

public:
    // UI Events
    virtual void MouseOn();

    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    virtual void MouseRBtnDown();
    virtual void MouseRBtnUP();
    virtual void MouseRBtnClicked();

    virtual CUI* Clone() = 0;

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};


