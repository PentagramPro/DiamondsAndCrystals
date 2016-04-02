#pragma once
#include "GameManager.h"
class GameManager;
class GameObject;

class SceneFactory
{
public:
	
	virtual ~SceneFactory() {};

	virtual void CreateScene(GameManager& manager, GameObject& root) = 0;
};