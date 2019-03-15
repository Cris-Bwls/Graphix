#include "OneApp.h"


int main()
{
	OneApp* app = new OneApp();
	bool test = app->Run("Graphix", 1280, 720, true);
	delete app;

	return 0;
}

