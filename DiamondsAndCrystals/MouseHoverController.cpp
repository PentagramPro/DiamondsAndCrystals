#include "MouseHoverController.h"



MouseHoverController::MouseHoverController()
{
}


MouseHoverController::~MouseHoverController()
{
}

void MouseHoverController::Init()
{
}

void MouseHoverController::Update(Uint32 timeDelta)
{
	if (Object()->IsMouseInside())
		Object()->m_alpha = 1;
	else
		Object()->m_alpha = 0.8f;
}
