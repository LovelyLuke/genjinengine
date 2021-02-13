#include "Genjin.h"

int main() {
	Genjin::GenjinEngine engine;
	engine.width = 640;
	engine.height = 480;
	engine.windowTitle = "My Genjin Game";
	//engine.fullscreen = true;
	engine.create();
	return 1;
}