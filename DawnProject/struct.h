#pragma once

struct Vec2
{
	float x;
	float y;


public:
	float Length() 
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize() 
	{
		float fLen = Length();

		//Exeption(0으로 나눌 때)
		assert(fLen != 0.f);
		
		
		x /= fLen; 
		y /= fLen;

		return *this;
	}

public:
	Vec2& operator = (POINT _pt) 
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator +(Vec2 _vOther) 
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	Vec2 operator -(Vec2 _vOther) 
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator *(Vec2 _vOther) 
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator /(Vec2 _vOther) 
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

public:
	Vec2()
		:x(0.f)
		,y(0.f)
	{}
	Vec2(float _x, float _y)
		:x(_x)
		,y(_y)
	{}
	Vec2(int _x, int _y)
		:x((float)_x)
		,y((float)_y)
	{}
};