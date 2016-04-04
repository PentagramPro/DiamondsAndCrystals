#pragma once
#include "Engine\Controller.h"
#include "CrystalController.h"
#include "GameController.h"
#include <memory>

#define FIELD_SIZE_X 8
#define FIELD_SIZE_Y 8
#define FALL_SHIFT 200
#define DRAG_DISTANCE 15

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

	void SetGlowPos(int cellX, int cellY);
	void Explode(int cellX, int cellY);
	void SwapCells(weak_ptr<CrystalController> cell1, weak_ptr<CrystalController> cell2);
	int TestField(bool createFx);
	inline bool Adjacent(int x1, int y1, int x2, int y2);

	States m_state;
	
	// stores swapped crystals for swapping them back in case they don't give
	// disappering rows/cols
	weak_ptr<CrystalController> m_swapped1, m_swapped2;

	weak_ptr<GameObject> m_glow;
	
};

