#pragma once


#define SINGLE(type) public:\
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

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535

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