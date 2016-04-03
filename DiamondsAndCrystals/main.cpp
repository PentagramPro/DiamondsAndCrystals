#include <exception>
#include <stdio.h>

#include "Engine\GameManager.h"
#include "DacSceneFactory.h"


int main(int argc, char* args[])
{
	
	try {
		DacSceneFactory factory;

		GameManager manager(factory);

		manager.Init();

		while (!manager.Loop())	{}
	}
	catch (GameManagerException& e)
	{
		printf("There was a problem running GameManager!\nException: %s\n", e.what());
		getchar();
	}
	catch (std::exception& e)
	{
		printf("There was a problem running GameManager!\nException: %s\n", e.what());
	}



	return 0;
}