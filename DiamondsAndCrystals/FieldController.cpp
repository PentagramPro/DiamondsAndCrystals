#include "FieldController.h"
#include "Engine\Constants.h"
#include "CrystalController.h"

#include <unordered_set>

using namespace std;

FieldController::FieldController()
{
}


FieldController::~FieldController()
{
}

void FieldController::Init()
{
	m_state = States::Idle;
	for (int cellX = 0; cellX < FIELD_SIZE_X; cellX++)
	{
		for (int cellY = 0; cellY < FIELD_SIZE_Y; cellY++)
		{
			auto crystal = std::make_shared<CrystalController>();

			crystal->m_cellX = cellX;
			crystal->m_cellY = cellY;
			
			
			crystal->m_field = dynamic_pointer_cast<FieldController>(shared_from_this());
			m_cells[cellY][cellX] = crystal;
			Object()->CreateObject("Crystal", 0, 0, NULL,crystal);
			
		}
	}
}

void FieldController::Update(Uint32 timeDelta)
{
	int cellX = (Manager().m_mouseX - Object()->m_localPosition.x) / CRYSTAL_SIZE;
	int cellY = (Manager().m_mouseY - Object()->m_localPosition.y) / CRYSTAL_SIZE;

	Vector2d mp(Manager().m_mouseX, Manager().m_mouseY);
	
	switch (m_state)
	{
	case States::Idle:
		if (Manager().m_mouseLeft == MB_UP && (cellX >= 0 && cellY >= 0 && cellX < FIELD_SIZE_X && cellY < FIELD_SIZE_Y))
		{
			FsaIdleMouse(cellX, cellY);
		}
		break;
	case States::Swap:
		if (m_movingCrystals == 0)
			FsaSwapped();
		break;
	case States::SwapBack:
		if (m_movingCrystals == 0)
			m_state = States::Idle;
	case States::Fall:
		if (m_movingCrystals == 0)
			FsaFallStopped();
		break;

	}

	m_movingCrystals = 0;


	

	
}

void FieldController::FsaIdleMouse(int cellX, int cellY)
{
	auto picked = m_pickedCell.lock();

	// this is basically an a AND (b XOR c) equation
	if (picked &&
		((abs(picked->m_cellX - cellX) == 1) != (abs(picked->m_cellY - cellY) == 1)))
	{
		SwapCells(m_cells[cellY][cellX], m_pickedCell);
		m_pickedCell.reset();
		m_state = States::Swap;
	}
	else
	{
		m_pickedCell = m_cells[cellY][cellX];
		printf("picked cell x:%d y:%d\n", cellX, cellY);
	}
}

void FieldController::FsaSwapped()
{
	int removed = TestField();
	if (removed > 0)
	{
		m_state = States::Fall;
	}
	else
	{
		SwapCells(m_swapped1, m_swapped2);
		m_state = States::SwapBack;
	}
}

void FieldController::FsaFallStopped()
{
	int removed = TestField();
	if (removed == 0)
	{
		m_state = States::Idle;
	}
}

void FieldController::SwapCells(weak_ptr<CrystalController> wcell1, weak_ptr<CrystalController> wcell2)
{
	m_swapped1 = wcell1;
	m_swapped2 = wcell2;

	auto cell1 = wcell1.lock();
	auto cell2 = wcell2.lock();

	int x = cell1->m_cellX;
	int y = cell1->m_cellY;

	printf("swapping cells[x,y]: [%d,%d] and [%d,%d] \n", cell1->m_cellX, cell1->m_cellY, cell2->m_cellX, cell2->m_cellY);

	cell1->m_cellX = cell2->m_cellX;
	cell1->m_cellY = cell2->m_cellY;


	cell2->m_cellX = x;
	cell2->m_cellY = y;

	//cell1->Object()->m_localPosition = cell1->Origin();
	//cell2->Object()->m_localPosition = cell2->Origin();

	m_cells[cell1->m_cellY][cell1->m_cellX] = wcell1;
	m_cells[cell2->m_cellY][cell2->m_cellX] = wcell2;

	//TestField();
}

int FieldController::TestField()
{
	unordered_set<shared_ptr<CrystalController>> toRemove;

	// Looking for 3 similar crystals in a row/col
	for (int cellX = 0; cellX < FIELD_SIZE_X; cellX++)
	{
		for (int cellY = 0; cellY < FIELD_SIZE_Y; cellY++)
		{
			auto cell = m_cells[cellY][cellX].lock();
			if (toRemove.count(cell))
				continue;
			int pos = cellX;
			while (++pos < FIELD_SIZE_X)
			{
				if (!cell->IsSame(m_cells[cellY][pos]))
				{
					--pos;
					break;
				}
			}

			if (pos == FIELD_SIZE_X)
				pos = FIELD_SIZE_X - 1;

			if (pos - cellX >= 2)
				while (pos >= cellX)
					toRemove.insert(m_cells[cellY][pos--].lock());

			pos = cellY;
			while (++pos < FIELD_SIZE_Y)
			{
				if (!cell->IsSame(m_cells[pos][cellX]))
				{
					--pos;
					break;
				}
			}
			if (pos == FIELD_SIZE_Y)
				pos = FIELD_SIZE_Y - 1;

			if (pos - cellY >= 2)
				while (pos >= cellY)
					toRemove.insert(m_cells[pos--][cellX].lock());

		}
	}


	// collecting all remaining crystals at the bottom
	int fallCount[FIELD_SIZE_X];
	memset(fallCount, 0, sizeof(fallCount));

	for (int cellX = 0; cellX < FIELD_SIZE_X; cellX++)
	{
		int pos = FIELD_SIZE_Y - 1;
		int count = 0;
		for (int cellY = FIELD_SIZE_Y - 1; cellY >= 0; cellY--)
		{
			auto cell = m_cells[cellY][cellX];
			if (toRemove.count(cell.lock()))
			{
				fallCount[cellX]++;
			}
			else
			{
				if(pos==cellY)
					pos = cellY - 1;
				else
				{
					m_cells[cellY][cellX] = m_cells[pos][cellX];
					m_cells[cellY][cellX].lock()->m_cellY = cellY;

					m_cells[pos][cellX] = cell;
					cell.lock()->m_cellY = pos;
					pos--;

				}
			}
		}
	}


	// placing all removed crystals at the very top of the field so they could fall down
	for (int cellX = 0; cellX < FIELD_SIZE_X; cellX++)
	{
		int count = fallCount[cellX];
		for (int cellY = 0; cellY < count; cellY++)
		{
			auto cell = m_cells[cellY][cellX].lock();
			cell->RandomizeColor();
			cell->Object()->m_localPosition.y = -FALL_SHIFT - (count - cellY)*CRYSTAL_SIZE;
		}
	}


	return toRemove.size();

}
