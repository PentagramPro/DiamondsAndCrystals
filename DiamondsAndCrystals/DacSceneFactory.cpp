#include "DacSceneFactory.h"
#include "FieldController.h"
#include "CrystalController.h"
#include "Engine\TextRenderer.h"
#include "Engine\SolidRenderer.h"
#include "GameController.h"
#include "FuseController.h"
#include "ParticlesController.h"
#include "MouseHoverController.h"

#include <memory>

using std::make_shared;

DacSceneFactory::DacSceneFactory()
{
}


DacSceneFactory::~DacSceneFactory()
{
}

void DacSceneFactory::CreateScene(GameManager & manager, GameObject & root)
{
	// Game
	auto gameController = make_shared<GameController>();
	GameObject& bg = root.CreateObject("Background", 0, 0, "BackGround.jpg",gameController );

	// Fuse
	auto fuseController = make_shared<FuseController>();
	fuseController->m_burnTime = TIME_LIMIT;
	fuseController->m_points.push_back(Vector2d(0, 0));
	fuseController->m_points.push_back(Vector2d(-12, -20));
	fuseController->m_points.push_back(Vector2d(-8, -39));
	fuseController->m_points.push_back(Vector2d(-51, -47));
	fuseController->m_points.push_back(Vector2d(-54, -184));
	fuseController->m_points.push_back(Vector2d(-87, -185));

	GameObject& fuse = bg.CreateObject("Fuse", 263, 555, NULL, fuseController);

	// Big Explosion
	auto bigBoomController = make_shared<ParticlesController>();
	bigBoomController->m_controllerLife = -1;
	bigBoomController->m_assetName = "Explosion.png";
	bigBoomController->m_burstSize = 0;
	bigBoomController->m_velocity = 400;
	bigBoomController->m_acceleration = -200;
	bigBoomController->m_life = 3000;
	bigBoomController->m_velocityNoise = 0.8f;
	GameObject& bigBoom = bg.CreateObject("BigBoom", 129, 329, NULL, bigBoomController);
	gameController->m_bigBoom = bigBoomController;


	// Field
	auto fieldController = make_shared<FieldController>();
	fieldController->m_gameController = gameController;
	fieldController->m_fuse = fuseController;
	GameObject& field = bg.CreateObject("Field", 330, 107, NULL, fieldController );
	gameController->m_field = fieldController;

	// Score
	TextRenderer* text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 60), { 0xff, 0xff,0xff,0xff });
	text->SetText("000000");
	auto textPtr = shared_ptr<TextRenderer>(text);
	GameObject& score = bg.CreateObject("Score", 20, 50, 180, 70, textPtr, NULL);
	gameController->m_scoreText = textPtr;

	// Timer
	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 70), { 0xff, 0x55,0x00,0xff });
	text->SetText("00");
	auto timerText = shared_ptr<TextRenderer>(text);
	GameObject& timer = bg.CreateObject("Timer", 75, 425, 180, 70, timerText, NULL);
	gameController->m_timerText = timerText;

	// Menu
	SolidRenderer* solid = new SolidRenderer();
	solid->SetColor(0, 0, 0, 220);
	GameObject& menu = root.CreateObject("Menu", 0, 0, manager.SCREEN_WIDTH, manager.SCREEN_HEIGHT,
		shared_ptr<SolidRenderer>(solid),NULL);
	gameController->m_menu = menu.GetSharedPtr();

	// Header text
	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 90), { 0xff, 0xff,0xff,0xff });
	text->SetText("Diamonds&Crystals");
	GameObject& headerText = menu.CreateObject("Header", 20, 30, 0, 0, shared_ptr<TextRenderer>(text), NULL);

	// Sign text
	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 30), { 0xff, 0xff,0xff,0xff });
	text->SetText("by Maxim Machekhin");
	GameObject& signText = menu.CreateObject("Sign", 30, 120, 0, 0, shared_ptr<TextRenderer>(text), NULL);

	// Best score text
	text = new TextRenderer(manager.GetRenderer());
	auto bestScorePtr = shared_ptr<TextRenderer>(text);
	text->SetFont(manager.LoadFont("Digital.ttf", 30), { 0xff, 0xff,0xff,0xff });
	text->SetText("Best score: 000000");
	GameObject& bestScore = menu.CreateObject("BestScore", 120, 230, 0, 0, bestScorePtr, NULL);
	gameController->m_bestScoreText = bestScorePtr;

	// Button
	solid = new SolidRenderer();
	solid->SetColor(0xe0, 0xa0, 0x20, 0xff);
	GameObject& startBtn = menu.CreateObject("StartButton", 280, 400, 200, 100, 
		shared_ptr<SolidRenderer>(solid), make_shared<MouseHoverController>());
	gameController->m_btnStart = startBtn.GetSharedPtr();

	// Button text
	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 90), { 0x00, 0x00,0x00,0xff });
	text->SetText("Start!");
	GameObject& startBtnText = startBtn.CreateObject("StartButtonText", 8, 0, 180, 70, shared_ptr<TextRenderer>(text), NULL);

}
