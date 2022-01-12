#include "Line.h"

/* Constructors / Destructor */
Line::Line()
{
	this->position1 = FVector(3U, new float[3]{ 0.0f });
	this->position2 = FVector(3U, new float[3]{ 0.0f });
	this->direction = FVector(3U, new float[3]{ 0.0f });
	this->color = FVector(3U, new float[3]{ 0.0f });
}
Line::Line(FVector position1, FVector position2, const FVector color)
{
	if (position1.getDimensions() != position2.getDimensions())
	{
		std::cout << "Warning: Vector dimensions are not equal" << std::endl;
		unsigned int maxDimensions = std::max(position1.getDimensions(), position2.getDimensions());
		position1.setDimensions(maxDimensions);
		position2.setDimensions(maxDimensions);
	}
	this->position1 = position1;
	this->position2 = position2;
	calculateDirection();
	this->color = color;
}
Line::Line(const Line& copy)
{
	*this = copy;
}
Line::~Line()
{
	;
}

/* Public Member Functions */
FVector Line::getPosition1() const	{ return position1; }
FVector Line::getPosition2() const	{ return position2; }
FVector Line::getDirection() const	{ return direction; }
FVector Line::getColor() const		{ return color; }
FVector Line::getMidpoint() const
{
	float* values = new float[position1.getDimensions()];
	for (int i = 0; i < position1.getDimensions(); i++)
	{
		// Gets half the distance in each dimension and adds it to the start position to generate the midpoint
		values[i] = position1[i] + (position2[i] - position1[i]) / 2;
	}

	return FVector(position1.getDimensions(), values);
}
float Line::getLength() const
{
	return (position2 - position1).getLength();
}
void Line::setPosition1(FVector position1)
{
	if (position1.getDimensions() != this->position2.getDimensions())
	{
		std::cout << "Warning: Vector dimensions are not equal" << std::endl;
		unsigned int maxDimensions = std::max(position1.getDimensions(), this->position2.getDimensions());
		position1.setDimensions(maxDimensions);
	}
	this->position1 = position1;
	calculateDirection();
}
void Line::setPosition2(FVector position2)
{
	if (this->position1.getDimensions() != position2.getDimensions())
	{
		std::cout << "Warning: Vector dimensions are not equal" << std::endl;
		unsigned int maxDimensions = std::max(this->position1.getDimensions(), position2.getDimensions());
		position2.setDimensions(maxDimensions);
	}
	this->position2 = position2;
	calculateDirection();
}
void Line::setPosition(FVector position1, FVector position2)
{
	if (position1.getDimensions() != position2.getDimensions())
	{
		std::cout << "Warning: Vector dimensions are not equal" << std::endl;
		unsigned int maxDimensions = std::max(position1.getDimensions(), position2.getDimensions());
		position1.setDimensions(maxDimensions);
		position2.setDimensions(maxDimensions);
	}
	this->position1 = position1;
	this->position2 = position2;
	calculateDirection();
}
void Line::setColor(const FVector color)
{
	this->color = color;
}

// Overloaded operators
Line& Line::operator= (const Line& copy)
{
	this->position1 = copy.getPosition1();
	this->position2 = copy.getPosition2();
	this->direction = copy.getDirection();
	this->color = copy.getColor();
	return *this;
}
bool Line::operator== (const Line& l)
{
	return (this->position1 == l.getPosition1() &&
		this->position2 == l.getPosition2() &&
		this->direction == l.getDirection() &&
		this->color == l.getColor());
}
bool Line::operator!= (const Line& l)
{
	return !((*this) == l);
}

/* Private Member Functions */
void Line::calculateDirection()
{
	direction = position2 - position1;
	direction.normalize();
}