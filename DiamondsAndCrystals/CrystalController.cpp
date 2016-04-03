#include "CrystalController.h"
#include <math.h>


string CrystalController::m_colors[] = { "Blue.png","Green.png","Purple.png","Red.png","Yellow.png" };

CrystalController::CrystalController()
{
}


CrystalController::~CrystalController()
{
}

void CrystalController::Init()
{
	int color = rand() % COLORS;
	Object()->SetTexture(m_colors[color]);

	Object()->m_localPosition.x = CRYSTAL_SIZE*m_cellX;
	Object()->m_localPosition.y = CRYSTAL_SIZE*m_cellY;

}

void CrystalController::Update()
{
}
