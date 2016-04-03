#pragma once
#include "Engine\Controller.h"
#include "CrystalController.h"
#include <memory>

#define FIELD_SIZE_X 8
#define FIELD_SIZE_Y 8
#define FALL_SHIFT 200

using std::weak_ptr;

class FieldController :
	public Controller
{
public:
	FieldController();
	virtual ~FieldController();


	virtual void Init();
	virtual void Update(Uint32 timeDelta);

	weak_ptr<CrystalController> m_cells[FIELD_SIZE_Y][FIELD_SIZE_X];

	weak_ptr<CrystalController> m_pickedCell;
protected:
	void SwapCells(weak_ptr<CrystalController> cell1, weak_ptr<CrystalController> cell2);
	int TestField();

};

