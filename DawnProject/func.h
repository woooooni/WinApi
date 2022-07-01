#pragma once

class CObject;

//event function
void CreateObj(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObj(CObject* _pObj);
void ChangeSceneEvt(SCENE_TYPE _eNext);


//템플릿은 헤더에 구현.
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
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