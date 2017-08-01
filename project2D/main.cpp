//#include "Application2D.h"
//
//int main() {
//	
//	// allocation
//	auto app = new Application2D();
//
//	// initialise and loop
//	app->run("AIE", 1280, 720, false);
//
//	// deallocation
//	delete app;
//
//	return 0;
//}

#include "NavMeshApp.h"

int main() {
	
	auto app = new NavMeshApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}