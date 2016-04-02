#pragma once
#include <memory>

#include "GameObject.h"

using std::weak_ptr;
class GameObject;

class Controller
{
	
public:
	Controller();
	virtual ~Controller();

	virtual void Init() = 0;
	virtual void Update() = 0;

	weak_ptr<GameObject> m_owner;
};

