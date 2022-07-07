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

#define CLONE(type) type* Clone() { return new type(*this); }

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535
#define TILE_SIZE 64	//2의 승수로 쓰면 최적화에 유리.

enum class GROUP_TYPE 
{
	DEFAULT,
	TILE,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	UI = 31,
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

enum class BRUSH_TYPE 
{
	HOLLOW,
	END,
};

enum class PEN_TYPE 
{
	RED, 
	GREEN, 
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,


	END,
};