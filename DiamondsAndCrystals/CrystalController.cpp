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
	
	RandomizeColor();
	Object()->m_localPosition = Origin();

}

void CrystalController::Update(Uint32 timeDelta)
{
	Vector2d origin = Origin();
	if (Object()->m_localPosition.y < origin.y - 0.1)
	{
		Object()->m_localPosition.y += FALL_SPEED*((float)timeDelta)/1000.0;
	}
}

void CrystalController::RandomizeColor()
{
	m_color = rand() % COLORS;
	Object()->SetTexture(m_colors[m_color]);
}

Vector2d CrystalController::Origin()
{
	return Vector2d(CRYSTAL_SIZE*m_cellX, CRYSTAL_SIZE*m_cellY);
}

bool CrystalController::IsSame(weak_ptr<CrystalController> cell)
{
	return cell._Get()->m_color == m_color;
}
