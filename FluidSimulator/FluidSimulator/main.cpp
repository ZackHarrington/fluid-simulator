#include "OpenGLWindow.h"
#include "Particle2D.h"

int main() {
	/* Init */
	OpenGLWindow window(false, "2D Fluid Simulation", 800, 600);				// Create a window




	/* Main loop */
	while (!window.shouldClose()) {
		// Run
		window.update();
	}


	/* Deallocation and clean up */
	window.deallocate();



	return 0;
}