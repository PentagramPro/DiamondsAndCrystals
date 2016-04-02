#include "GameObject.h"




GameObject::GameObject(GameManager& manager) : m_manager(manager),
	m_name("GameObject")
{
	memset(&m_rect, 0, sizeof(m_rect));
}

GameObject::GameObject(const char*  name, int x, int y, int sizeX, int sizeY, GameManager& manager) : m_manager(manager),
m_name(name)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.h = sizeY;
	m_rect.w = sizeX;
}


GameObject::~GameObject()
{
}

void GameObject::Update(Uint32 timeDelta)
{
}

void GameObject::Render()
{
	
	

	// potential place for matrix transformations
	if (m_texture != NULL)
		SDL_RenderCopy(m_manager.GetRenderer(), m_texture, NULL, &m_rect);

	for (auto& item : m_children)
		item->Render();
}


GameObject & GameObject::CreateObject(const char* name, int x, int y, const char* textureAsset, Controller* controller)
{
	GameObject* res = new GameObject(name,x,y,0,0,m_manager);
	res->m_controller = controller;
	res->m_texture = m_manager.LoadTexture(textureAsset);
	SDL_QueryTexture(res->m_texture, NULL, NULL, &res->m_rect.w, &res->m_rect.h);

	m_children.push_back(unique_ptr<GameObject>(res));

	return *res;
}
