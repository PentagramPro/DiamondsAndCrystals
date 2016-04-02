#include "GameObject.h"






GameObject::GameObject(GameManager& manager) : m_manager(manager),
	m_name("GameObject"), m_localPosition(0, 0), m_globalPosition(0, 0)
{
	memset(&m_rect, 0, sizeof(m_rect));
	m_parent = NULL;
	m_texture = NULL;
}

GameObject::GameObject(const char*  name, float x, float y, int sizeX, int sizeY, GameManager& manager) : m_manager(manager),
m_name(name), m_localPosition(x,y), m_globalPosition(0,0)
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.h = sizeY;
	m_rect.w = sizeX;
	m_parent = NULL;
	m_texture = NULL;
		
}


GameObject::~GameObject()
{
}

void GameObject::Update(Uint32 timeDelta)
{
	if (m_parent != NULL)
		m_globalPosition = m_localPosition + m_parent->m_globalPosition;

	for (auto& item : m_children)
		item->Update(timeDelta);

	m_rect.x = roundf(m_globalPosition.x);
	m_rect.y = roundf(m_globalPosition.y);
}

void GameObject::Render()
{
	
	

	// potential place for matrix transformations
	if (m_texture != NULL)
		SDL_RenderCopy(m_manager.GetRenderer(), m_texture, NULL, &m_rect);

	for (auto& item : m_children)
		item->Render();
}

shared_ptr<GameObject> GameObject::GetSharedPtr()
{
	return shared_from_this();
}

GameObject & GameObject::CreateObject(const char* name, float x, float y, const char* textureAsset, Controller* controller)
{
	shared_ptr<GameObject> res(new GameObject(name, x, y, 0, 0, m_manager));
	
	if (controller != NULL)
		controller->m_owner = GetSharedPtr();
	res->m_controller.reset(controller);
	if(textureAsset!=NULL)
		res->m_texture = m_manager.LoadTexture(textureAsset);
	res->m_parent = GetSharedPtr();
	SDL_QueryTexture(res->m_texture, NULL, NULL, &res->m_rect.w, &res->m_rect.h);

	m_children.push_back(res);

	return *res;
}
