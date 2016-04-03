#include "FieldController.h"


#define FIELD_SIZE_X 8
#define FIELD_SIZE_Y 8

FieldController::FieldController()
{
}


FieldController::~FieldController()
{
}

void FieldController::Init()
{
	for (int cellX = 0; cellX < FIELD_SIZE_X; cellX++)
	{
		for (int cellY = 0; cellY < FIELD_SIZE_Y; cellY++)
		{
			auto crystal = std::make_shared<CrystalController>();

			crystal->m_cellX = cellX;
			crystal->m_cellY = cellY;

			Object()->CreateObject("Crystal", 0, 0, NULL,crystal);
			
		}
	}
}

void FieldController::Update()
{
}
