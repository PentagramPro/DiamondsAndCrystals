#include "DacSceneFactory.h"
#include "FieldController.h"
#include "CrystalController.h"
#include "Engine\TextRenderer.h"
#include "Engine\SolidRenderer.h"
#include "GameController.h"

#include <memory>
DacSceneFactory::DacSceneFactory()
{
}


DacSceneFactory::~DacSceneFactory()
{
}

void DacSceneFactory::CreateScene(GameManager & manager, GameObject & root)
{
	auto gameController = std::make_shared<GameController>();
	GameObject& bg = root.CreateObject("Background", 0, 0, "BackGround.jpg",gameController );

	auto fieldController = std::make_shared<FieldController>();
	fieldController->m_gameController = gameController;
	GameObject& field = bg.CreateObject("Field", 330, 107, NULL, fieldController );
	gameController->m_field = fieldController;

	TextRenderer* text = new TextRenderer(manager.GetRenderer());
	
	text->SetFont(manager.LoadFont("Digital.ttf", 60), { 0xff, 0xff,0xff,0xff });
	text->SetText("000000");
	auto textPtr = shared_ptr<TextRenderer>(text);
	GameObject& score = bg.CreateObject("Score", 20, 50, 180, 70, textPtr, NULL);
	gameController->m_scoreText = textPtr;

	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 60), { 0xbe, 0xbe,0xff,0xff });
	text->SetText("60");
	auto timerText = shared_ptr<TextRenderer>(text);
	GameObject& timer = bg.CreateObject("Timer", 70, 150, 180, 70, timerText, NULL);
	gameController->m_timerText = timerText;

	SolidRenderer* solid = new SolidRenderer();
	solid->SetColor(0, 0, 0, 200);
	GameObject& menu = root.CreateObject("Menu", 0, 0, manager.SCREEN_WIDTH, manager.SCREEN_HEIGHT,
		shared_ptr<SolidRenderer>(solid),NULL);
	gameController->m_menu = menu.GetSharedPtr();

	solid = new SolidRenderer();
	solid->SetColor(0xe0, 0xa0, 0x20, 0xff);
	GameObject& startBtn = menu.CreateObject("StartButton", 300, 400, 200, 100, shared_ptr<SolidRenderer>(solid), NULL);
	gameController->m_btnStart = startBtn.GetSharedPtr();

	text = new TextRenderer(manager.GetRenderer());
	text->SetFont(manager.LoadFont("Digital.ttf", 90), { 0x00, 0x00,0x00,0xff });
	text->SetText("Start!");
	GameObject& startBtnText = startBtn.CreateObject("StartButtonText", 8, 0, 180, 70, shared_ptr<TextRenderer>(text), NULL);

}
