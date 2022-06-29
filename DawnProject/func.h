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
