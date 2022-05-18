#pragma once


#define SINGLE(type) public: \
						static type* GetInst()\
						{\
							static type manager;\
							return &manager;\
						}\
						private:\
							type();\
							~type();


#define DeltaTimef CTimeMgr::GetInst()->GetfDT()
#define DeltaTime CTimeMgr::GetInst()->GetDT()