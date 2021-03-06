#pragma once

class CObject;
class AI;

//event function
void CreateObj(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObj(CObject* _pObj);
void ChangeSceneEvt(SCENE_TYPE _eNext);
void ChangeAIState(AI* _pAI, MONSTER_STATE _eNext);

//file function
void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);

//템플릿은 헤더에 구현.
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}

template <typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	//템플릿 함수 내에서 이너클래스 사용 시 typename 적어줘야함.
	typename map<T1, T2>::iterator iter = _map.begin();
	for (;iter != _map.end(); iter++)
	{
		if(iter->second)
			delete iter->second;
	}
	_map.clear();
}

template<typename T1>
T1 clamp(T1 src, T1 min, T1 max)
{
	if (src > max)
		return max;
	if (src < min)
		return min;
	return src;
}

template<typename T1>
void swap(T1* t1, T1* t2)
{
	T1 temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}