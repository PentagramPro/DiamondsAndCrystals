#include "DacSceneFactory.h"



DacSceneFactory::DacSceneFactory()
{
}


DacSceneFactory::~DacSceneFactory()
{
}

void DacSceneFactory::CreateScene(GameManager & manager, GameObject & root)
{
	root.CreateObject("Background", 0, 0, "BackGround.jpg", NULL);
}
