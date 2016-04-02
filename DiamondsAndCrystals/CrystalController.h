#pragma once
#include "Engine\Controller.h"
class CrystalController :
	public Controller
{
public:
	CrystalController();
	virtual ~CrystalController();

	virtual void Init();
	virtual void Update();
};

