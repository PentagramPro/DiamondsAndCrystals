#pragma once
#include "Engine\Controller.h"
#include "Engine\TextRenderer.h"
#include <memory>

#include "FieldController.h"
using std::weak_ptr;

#define SCORE_PER_CELL 10
#define TIME_LIMIT 60
class FieldController;

class GameController :
	public Controller
{
public:
	GameController();
	virtual ~GameController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);

	weak_ptr<TextRenderer> m_scoreText;
	void AddScore(int cellsRemoved);

	weak_ptr<GameObject> m_btnStart;
	weak_ptr<GameObject> m_menu;
	weak_ptr<FieldController> m_field;
	weak_ptr<TextRenderer> m_timerText;
protected:
	enum class States{Menu,Game};
	States m_state;
	int m_score;
	int m_time;
};

