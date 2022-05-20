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


enum class GROUP_TYPE 
{
	DEFAULT,
	PLAYER,
	PROJECTILE,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE 
{
	TOOL,
	START,

	STAGE_01,
	STAGE_02,

	END,
};