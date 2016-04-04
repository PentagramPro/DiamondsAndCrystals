#include "GameController.h"



GameController::GameController() : m_score(0)
{
}


GameController::~GameController()
{
}

void GameController::Init()
{
	m_state = States::Menu;
}

void GameController::Update(Uint32 timeDelta)
{
	if (m_state == States::Menu)
	{
		if (Manager().m_mouseLeft == MB_UP && m_btnStart.lock()->IsMouseInside())
		{
			m_time = 0;
			m_state = States::Game;
			m_menu.lock()->SetEnabled(false);
			m_field.lock()->StartNewGame();
		}
	}
	else if(m_state==States::Game)
	{
		m_time += timeDelta;
		int secondsLeft = TIME_LIMIT-m_time / 1000;
		if (secondsLeft < 0)
		{
			m_time = 0;
			m_state = States::Explosion;
			m_bigBoom.lock()->Burst(100);
			m_field.lock()->EndGame();
		}
		else
		{
			char buf[5];
			snprintf(buf, sizeof(buf), "%02d", secondsLeft);

			m_timerText.lock()->SetText(buf);
		}
	}
	else
	{
		m_time += timeDelta;
		int secondsLeft = EXPLOSION_TIME - m_time / 1000;
		if (secondsLeft < 0)
		{
			m_state = States::Menu;
			m_menu.lock()->SetEnabled(true);
		}
	}
}

void GameController::AddScore(int cellsRemoved)
{
	m_score += cellsRemoved*SCORE_PER_CELL;
	char buf[10];
	snprintf(buf, sizeof(buf), "%06d", m_score);
	m_scoreText.lock()->SetText(buf);
}
