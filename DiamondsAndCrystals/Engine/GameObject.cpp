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
	

	if (m_controller.get() != NULL)
		m_controller->Update(timeDelta);

	for (auto& item : m_children)
		item->Update(timeDelta);

	if (m_parent != NULL)
		m_globalPosition = m_localPosition + m_parent->m_globalPosition;

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

void GameObject::SetTexture(string assetName)
{
	m_texture = m_manager.LoadTexture(assetName);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);

}

int GameObject::Width()
{
	
	return m_rect.w;
}

int GameObject::Height()
{
	return m_rect.h;
}

bool GameObject::IsMouseInside()
{
	return (m_manager.m_mouseX > m_rect.x && m_manager.m_mouseX<m_rect.x + m_rect.w) &&
		(m_manager.m_mouseY>m_rect.y && m_manager.m_mouseY < m_rect.y + m_rect.h);

}

GameObject & GameObject::CreateObject(const char* name, float x, float y, const char* textureAsset, shared_ptr<Controller> controller)
{
	shared_ptr<GameObject> res(new GameObject(name, x, y, 0, 0, m_manager));
	
	if (controller != NULL)
	{
		controller->m_owner = res;
		controller->Init();
	}
	res->m_controller=controller;
	if (textureAsset != NULL)
		res->SetTexture(textureAsset);
	res->m_parent = GetSharedPtr();
	
	m_children.push_back(res);
	

	return *res;
}
