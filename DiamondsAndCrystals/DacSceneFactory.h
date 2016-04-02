#pragma once
#include "Engine\SceneFactory.h"

class DacSceneFactory :
	public SceneFactory
{
public:
	DacSceneFactory();
	virtual ~DacSceneFactory();

	virtual void CreateScene(GameManager& manager, GameObject& root);
};

