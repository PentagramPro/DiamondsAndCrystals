#include "DacSceneFactory.h"
#include "FieldController.h"
#include "CrystalController.h"

#include <memory>
DacSceneFactory::DacSceneFactory()
{
}


DacSceneFactory::~DacSceneFactory()
{
}

void DacSceneFactory::CreateScene(GameManager & manager, GameObject & root)
{
	GameObject& bg = root.CreateObject("Background", 0, 0, "BackGround.jpg", NULL);

	GameObject& field = bg.CreateObject("Field", 330, 107, NULL, std::make_shared<FieldController>());
}
