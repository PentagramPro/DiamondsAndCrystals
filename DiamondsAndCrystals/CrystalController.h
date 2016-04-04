#pragma once
#include "Engine\Controller.h"
#include "FieldController.h"

#include <string>

#define COLORS 5
#define CRYSTAL_SIZE 42
#define FALL_SPEED 100.0
#define FALL_ACC 600.0

using std::string;
class FieldController;

class CrystalController :
	public Controller
{
public:
	
	CrystalController();
	virtual ~CrystalController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);
	void RandomizeColor();
	
	void SetColorAndPos(int color);

	int m_cellX, m_cellY;
	weak_ptr<FieldController> m_field;

	static string m_colors[COLORS];

	Vector2d Origin();
	int m_color;
	float m_fallSpeed;
	bool IsSame(weak_ptr<CrystalController> cell);
};

