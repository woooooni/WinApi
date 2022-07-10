#pragma once
#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

//��� Ŭ������ �ֻ��� �θ�Ŭ���� �ϳ��� ��ӹ޴� ������ ����� �ȴٸ�, ��� Ŭ���� ����Լ��� ���� �� ����
typedef void (CScene::*SCENE_MEMFUNC)(void);
typedef void (CObject::* OBJECT_MEMFUNC)(void);

class CButtonUI :
    public CUI
{
private:
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*    m_pSceneInst;
public:
    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    void SetClickedCallBack(BTN_FUNC _pCallback, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pCallback;
        m_param1 = _param1;
        m_param2 = _param2;
    };

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneInst = _pScene;
        m_pSceneFunc = _pSceneFunc;
    };
    
public:
    CButtonUI();
    ~CButtonUI();

    CLONE(CButtonUI);
};


