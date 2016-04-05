#pragma once
#include "Engine\Controller.h"
class MouseHoverController :
	public Controller
{
public:
	MouseHoverController();
	virtual ~MouseHoverController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);
};

