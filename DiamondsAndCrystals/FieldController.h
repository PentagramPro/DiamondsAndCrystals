#pragma once
#include "Engine\Controller.h"
#include "CrystalController.h"
#include "GameController.h"
#include <memory>

#define FIELD_SIZE_X 8
#define FIELD_SIZE_Y 8
#define FALL_SHIFT 200

using std::weak_ptr;
class CrystalController;
class GameController;

class FieldController :
	public Controller
{
public:
	enum class States {
		Paused,PauseDelay,Idle, Swap, SwapBack, Fall
	};
	FieldController();
	virtual ~FieldController();


	virtual void Init();
	virtual void Update(Uint32 timeDelta);

	weak_ptr<CrystalController> m_cells[FIELD_SIZE_Y][FIELD_SIZE_X];

	weak_ptr<CrystalController> m_pickedCell;
	int m_movingCrystals;
	weak_ptr<GameController> m_gameController;

	void StartNewGame();
	void EndGame();
protected:

	void FsaIdleMouse(int cellX, int cellY);
	void FsaSwapped();
	void FsaFallStopped();

	void SwapCells(weak_ptr<CrystalController> cell1, weak_ptr<CrystalController> cell2);
	int TestField();

	States m_state;

	weak_ptr<CrystalController> m_swapped1, m_swapped2;

};

