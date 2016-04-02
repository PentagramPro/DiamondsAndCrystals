#include "DacSceneFactory.h"
#include "FieldController.h"
#include "CrystalController.h"


DacSceneFactory::DacSceneFactory()
{
}


DacSceneFactory::~DacSceneFactory()
{
}

void DacSceneFactory::CreateScene(GameManager & manager, GameObject & root)
{
	GameObject& bg = root.CreateObject("Background", 0, 0, "BackGround.jpg", NULL);

	GameObject& field = bg.CreateObject("Field", 313, 96, NULL, new FieldController());
}
