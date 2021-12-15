#include "OpenGLWindow.h"

int main() {
	/* Init */
	OpenGLWindow window(false, 800, 600);				// Create a window




	/* Main loop */
	while (!window.shouldClose()) {
		// Run
		window.update();
	}


	/* Deallocation and clean up */
	window.deallocate();



	return 0;
}