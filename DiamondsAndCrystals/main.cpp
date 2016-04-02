#include <exception>
#include <stdio.h>

#include "GameManager.h"



int main(int argc, char* args[])
{
	
	
	try {
		GameManager manager;

		manager.Init();

		while (!manager.Loop())
		{

		}


	}
	catch (std::exception& e)
	{
		printf("There was a problem running GameManager!\nException: %s\n", e.what());
	}

	

	
	

	

	return 0;
}