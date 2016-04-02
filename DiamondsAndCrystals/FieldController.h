#pragma once
#include "Engine\Controller.h"


class FieldController :
	public Controller
{
public:
	FieldController();
	virtual ~FieldController();


	virtual void Init();
	virtual void Update();
};

