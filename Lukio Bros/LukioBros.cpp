#include "Core.h"

int main() {
	LB_INFO("Starting LukioBorsEngine v0.1 by radston12");
	Engine::Window w;// Inits Window and starts game -> Blocks thread until its ready to destroy(Game is running)
	w.Destroy();
	return 0;
}

