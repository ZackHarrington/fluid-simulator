#include "Simulation2D.h"

int main() {
	/* Init */
	Simulation2D* sim = new Simulation2D(false, "Title goes here", 1024U, 1024U);



	/* Main loop */
	while (!sim->shouldClose()) {
		// Run
		sim->update();
	}


	/* Deallocation and clean up */
	sim->deallocate();



	return 0;
}