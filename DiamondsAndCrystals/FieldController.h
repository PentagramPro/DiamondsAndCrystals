#pragma once
#include "Engine\Controller.h"
#include "CrystalController.h"

class FieldController :
	public Controller
{
public:
	FieldController();
	virtual ~FieldController();


	virtual void Init();
	virtual void Update();
};

