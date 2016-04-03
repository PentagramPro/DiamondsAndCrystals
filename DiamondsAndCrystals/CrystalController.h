#pragma once
#include "Engine\Controller.h"
#include <string>

#define COLORS 5
#define CRYSTAL_SIZE 42

using std::string;

class CrystalController :
	public Controller
{
public:
	CrystalController();
	virtual ~CrystalController();

	virtual void Init();
	virtual void Update();

	int m_cellX, m_cellY;

	static string m_colors[COLORS];
};

