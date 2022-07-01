#pragma once

class CObject;

//event function
void CreateObj(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObj(CObject* _pObj);
void ChangeSceneEvt(SCENE_TYPE _eNext);


//���ø��� ����� ����.
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
	//���ø� �Լ� ������ �̳�Ŭ���� ��� �� typename ���������.
	typename map<T1, T2>::iterator iter = _map.begin();
	for (;iter != _map.end(); iter++)
	{
		if(iter->second)
			delete iter->second;
	}
	_map.clear();
}