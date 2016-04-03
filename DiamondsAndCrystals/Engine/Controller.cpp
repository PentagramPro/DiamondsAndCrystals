#include "Controller.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

GameObject * Controller::Object()
{
	if (m_owner.expired())
		throw GameManagerException("Tried to access to a GameObject that was already removed","");

	return m_owner._Get();
}

GameManager & Controller::Manager()
{
	
	return Object()->Manager();
}
