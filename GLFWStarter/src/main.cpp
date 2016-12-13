
#include "Game1.h"

int main(int argc, char **argv)
{
	Applaction *pApp = new Game1();

	if (pApp->SetUp(640, 480)) {
		pApp->Run();
		pApp->shutDown();
	}

	delete pApp;

    return 0;
}