#pragma once
#include <memory>

#include "GameObject.h"

using std::weak_ptr;
using std::shared_ptr;
class GameObject;

class Controller : public std::enable_shared_from_this<Controller>
{
	
public:
	Controller();
	virtual ~Controller();

	virtual void Init() = 0;
	virtual void Update() = 0;

	weak_ptr<GameObject> m_owner;
	shared_ptr<Controller> GetSharedPtr() { return shared_from_this(); }

protected:
	GameObject* Object();
};

