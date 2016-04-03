#pragma once
#include "Engine\Controller.h"
#include <string>

#define COLORS 5
#define CRYSTAL_SIZE 42
#define FALL_SPEED 220.5

using std::string;

class CrystalController :
	public Controller
{
public:
	enum class States {
		Idle,
	};
	CrystalController();
	virtual ~CrystalController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);
	void RandomizeColor();

	int m_cellX, m_cellY;

	static string m_colors[COLORS];

	Vector2d Origin();
	int m_color;
	bool IsSame(weak_ptr<CrystalController> cell);
};

