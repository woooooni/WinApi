#pragma once
class CUIMgr
{
	SINGLE(CUIMgr);
private:

public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI); //	�θ�UI������ ������ Ÿ���õ� UI�� ã�� ��ȯ.
};

