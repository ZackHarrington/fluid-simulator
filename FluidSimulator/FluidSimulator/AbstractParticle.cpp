#include "AbstractParticle.h"

/* Constructor */
AbstractParticle::AbstractParticle()
{
	this->radius = 1.0f;
	this->mass = 1.0f;
	FVector nullVector(3U, new float[] {0.0f, 0.0f, 0.0f});
	this->position = nullVector;
	this->velocity = nullVector;
	this->color = nullVector;
}
AbstractParticle::AbstractParticle(const float radius, const float mass, 
	const FVector position, const FVector velocity, const FVector color)
{
	this->radius = radius;
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->color = color;
}
AbstractParticle::~AbstractParticle()
{
	;
}


/* Public Member Functions */
float AbstractParticle::getRadius() const				{ return radius; }
float AbstractParticle::getMass() const					{ return mass; }
FVector AbstractParticle::getPosition() const			{ return position; }
FVector AbstractParticle::getVelocity() const			{ return velocity; }
FVector AbstractParticle::getColor() const				{ return color; }

void AbstractParticle::setRadius(const float radius)		{ this->radius = radius; }
void AbstractParticle::setRadius(const int radius)			{ this->radius = (float)radius; }
void AbstractParticle::setRadius(const double radius)		{ this->radius = (float)radius; }
void AbstractParticle::setMass(const float mass)			{ this->mass = mass; }
void AbstractParticle::setMass(const int mass)				{ this->mass = (float)mass; }
void AbstractParticle::setMass(const double mass)			{ this->mass = (float)mass; }
void AbstractParticle::setPosition(const FVector position)	{ this->position = position; }
void AbstractParticle::setVelocity(const FVector velocity)	{ this->velocity = velocity; }
void AbstractParticle::setColor(const FVector color)		{ this->color = color; }

void AbstractParticle::update(const float timeMultiplier)
{
	position = position + velocity * timeMultiplier;
}