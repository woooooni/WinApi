#pragma once
#include "CComponent.h"
class CStateMachine
	: public CComponent
{
private:

public:
	virtual void finalupdate();
	virtual void render(HDC _dc);
public:
	CStateMachine();
	~CStateMachine();
};

