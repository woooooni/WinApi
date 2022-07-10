#pragma once
#include "CScene.h"

class CUI;
class CScene_Tool :
    public CScene
{
private:
    CUI* m_pUI;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIndex();

    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);

    void LoadTileData();
public:
    CScene_Tool();
    ~CScene_Tool();
};

