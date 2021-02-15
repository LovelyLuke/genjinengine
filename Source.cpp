#include "Genjin.h"

int main() {
	Genjin::GenjinEngine engine;
	engine.width = 1300;
	engine.height = 700;
	engine.windowTitle = "Genjin Preview";
	engine.vignette = true;
	engine.create();
	return 1;
}