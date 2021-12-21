#include "AbstractParticle.h"

/* Constructor */
AbstractParticle::AbstractParticle(float radius, float mass, FVector position, FVector velocity, FVector color)
{
	this->radius = radius;
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->color = color;
}


/* Public Member Functions */
float AbstractParticle::getRadius() const				{ return radius; }
float AbstractParticle::getMass() const					{ return mass; }
FVector AbstractParticle::getPosition() const			{ return position; }
FVector AbstractParticle::getVelocity() const			{ return velocity; }
FVector AbstractParticle::getColor() const				{ return color; }

void AbstractParticle::setRadius(float radius)			{ this->radius = radius; }
void AbstractParticle::setRadius(int radius)			{ this->radius = (float)radius; }
void AbstractParticle::setRadius(double radius)			{ this->radius = (float)radius; }
void AbstractParticle::setMass(float mass)				{ this->mass = mass; }
void AbstractParticle::setMass(int mass)				{ this->mass = (float)mass; }
void AbstractParticle::setMass(double mass)				{ this->mass = (float)mass; }
void AbstractParticle::setPosition(FVector position)	{ this->position = position; }
void AbstractParticle::setVelocity(FVector velocity)	{ this->velocity = velocity; }
void AbstractParticle::setColor(FVector color)			{ this->color = color; }