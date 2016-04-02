#include "GameManager.h"


GameManager::GameManager(SceneFactory& sceneFactory) : m_sceneFactory(sceneFactory),
	SCREEN_HEIGHT(600), SCREEN_WIDTH(755)
{
	m_sceneRoot = new GameObject(*this);
}


GameManager::~GameManager()
{
	Deinit();
	delete m_sceneRoot;
}

void GameManager::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw GameManagerException("SDL_Init returned error: ", SDL_GetError());
	
	m_window = SDL_CreateWindow("Diamonds and Crystals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		throw GameManagerException("SDL_CreateWindow couldn't create window: ", SDL_GetError());
		
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if(m_renderer == NULL)
		throw GameManagerException("SDL_CreateRenderer couldn't create renderer: ", SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw GameManagerException("Couldn't initialize png loader: ", IMG_GetError());

	m_sceneFactory.CreateScene(*this, *m_sceneRoot);

	m_loopEndTime = SDL_GetTicks();
}

bool GameManager::Loop()
{
	bool quit = false;
	SDL_Event evnt;

	// SDL_GetTicks wraps after 49 days of running the game, but player will starve to death to that time
	// I dont use timer events since this game contains only player-dependent actions
	Uint32 timeDelta = SDL_GetTicks() - m_loopEndTime;

	while (SDL_PollEvent(&evnt) != 0)
	{
		if (evnt.type == SDL_QUIT)
		{
			quit = true;
		}
	}

	SDL_RenderClear(m_renderer);

	m_sceneRoot->Update(timeDelta);
	m_sceneRoot->Render();

	SDL_RenderPresent(m_renderer);

	return quit;
}

SDL_Texture * GameManager::LoadTexture(string assetName)
{
	if (m_textures.count(assetName) > 0)
		return m_textures[assetName];

	SDL_Surface* loadedSurface = IMG_Load(("Assets\\"+assetName).c_str());
	if (loadedSurface == NULL)
		throw GameManagerException(("Cannot load texture " + assetName+": ").c_str(), SDL_GetError());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	
	if (texture == NULL)
		throw GameManagerException("Cannot create texture: ", SDL_GetError());
	
	m_textures[assetName] = texture;
	return texture;
}

SDL_Renderer * GameManager::GetRenderer()
{
	return m_renderer;
}

void GameManager::Deinit()
{

	for (auto item : m_textures)
		SDL_DestroyTexture(item.second);

	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;

	SDL_DestroyWindow(m_window);
	m_window = NULL;

	SDL_Quit();
}
