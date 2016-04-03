#include "GameManager.h"


GameManager::GameManager(SceneFactory& sceneFactory) : m_sceneFactory(sceneFactory),
	SCREEN_HEIGHT(600), SCREEN_WIDTH(755)
{
	m_sceneRoot.reset(new GameObject(*this));
}


GameManager::~GameManager()
{
	Deinit();
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

	if (TTF_Init() == -1)
		throw GameManagerException("Couldn't initialize ttf library: ", TTF_GetError());
		

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
	m_loopEndTime = SDL_GetTicks();

	Uint32 mouseButtons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

	m_mouseLeft = MouseState(m_mouseLeft, mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT));
	m_mouseRight = MouseState(m_mouseLeft, mouseButtons & SDL_BUTTON(SDL_BUTTON_RIGHT));
	
	while (SDL_PollEvent(&evnt) != 0)
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		
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

TTF_Font * GameManager::LoadFont(string assetName, int size)
{
	pair<string, int> p(assetName, size);
	if (m_fonts.count(p) > 0)
		return m_fonts[p];

	TTF_Font* loadedFont = TTF_OpenFont(("Assets\\" + assetName).c_str(), size);
	if (loadedFont == NULL)
		throw GameManagerException(("Cannot load font " + assetName + ": ").c_str(), SDL_GetError());
	


	m_fonts[p] = loadedFont;
	return loadedFont;
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

inline int GameManager::MouseState(int curFromGm, int curFromSdl)
{
	static int convTable[2][4] = { {0,3,3,0},{1,2,2,1} };
	if (curFromSdl != 0)
		curFromSdl = 1;
	return convTable[curFromSdl][curFromGm];
}
