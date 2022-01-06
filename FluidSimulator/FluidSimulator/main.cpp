#include "Simulation2D.h"
#include "OpenGLWindow.h"
#include "Particle2D.h"

int main() {
	/* Init */															// *** Adjustable settings ***
	Simulation2D simulation(ColoringStyle::SPEED_FACTORY, 150U);		// coloring style, number of particles
	OpenGLWindow drawWindow(false, "Title goes here", 1024U, 1024U);	// fullscreen, title, screen width, screen height
	float lastTime = glfwGetTime();
	float deltaTime = 0;

	// Set VBO with basic particle
	FVector zeroVec3D = FVector(3U);
	Particle2D basicParticle(1.0f, 1.0f, zeroVec3D, zeroVec3D, zeroVec3D);
	unsigned int resolution = 8;										// number of vertices / line segments on polygon
	drawWindow.setVBOFromParticle(&basicParticle, resolution, true);

	/* Main loop */
	while (!drawWindow.shouldClose()) 
	{
		// Check the change in time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastTime;
		lastTime = currentFrame;

		// Run
		simulation.update(deltaTime);

		// Draw
		drawWindow.draw(simulation.getParticleData(), simulation.getNumParticles(),
			false, simulation.getColoringStyle());						// set one ball to red
	}


	/* Deallocation and clean up */
	simulation.deallocate();
	drawWindow.deallocate();



	return 0;
}