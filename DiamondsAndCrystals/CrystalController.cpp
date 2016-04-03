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
	Vector2d shift = origin - Object()->m_localPosition;
	float dist = shift.Magnitude();
	
	if ( dist > 0.1)
	{
		shift.Normalize();
		shift *= (m_fallSpeed*((float)timeDelta) / 1000.0);
		m_fallSpeed += FALL_ACC*(float)timeDelta/1000.0;

		if (shift.Magnitude() > dist)
			Object()->m_localPosition = origin;
		else
			Object()->m_localPosition +=  shift;
		m_field.lock()->m_movingCrystals++;
	}
	else
	{
		m_fallSpeed = FALL_SPEED;
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
