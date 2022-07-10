#pragma once
class CUI;
class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);
private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI); //	부모UI내에서 실제로 타겟팅된 UI를 찾아 반환.
};

