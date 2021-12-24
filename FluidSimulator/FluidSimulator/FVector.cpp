#include "FVector.h"

/* Constructors / Destructors */
FVector::FVector(unsigned int dimensions, float* values)
{
	if (dimensions == 0)
		std::cout << "Warning: 0 dimensional vector created" << std::endl;

	this->dimensions = dimensions;
	this->values = new float[this->dimensions];
	if (values == nullptr)
	{
		for (int i = 0; i < this->dimensions; i++)
			this->values[i] = 0.0f;
	}
	else
	{
		for (int i = 0; i < this->dimensions; i++)
			this->values[i] = values[i];
	}
}
FVector::FVector(const FVector& copy)
{
	dimensions = copy.getDimensions();
	values = new float[dimensions];
	for (int i = 0; i < dimensions; i++)
		values[i] = copy.getValues()[i];
}

FVector::~FVector()
{
	// Add the brackets when it's an array
	delete[] values;
}


/* Public Member Functions */
unsigned int FVector::getDimensions() const { return dimensions; }
float* FVector::getValues() const { return values; }

void FVector::setDimensions(unsigned int dimensions)
{
	if (this->dimensions > dimensions)					// shrink the vector
	{
		float* oldValues = values;
		values = new float[dimensions];
		for (int i = 0; i < dimensions; i++)
			values[i] = oldValues[i];

		this->dimensions = dimensions;
	}
	else if (this->dimensions < dimensions)				// grow the vector
	{
		float* oldValues = values;
		values = new float[dimensions];
		for (int i = 0; i < dimensions; i++)
		{
			// i + 1 because if this.dimension == 3 and the new dimensions == 4; 0 <= i <= 3 
			// so on the last itteration we need to make sure we don't over step the previous values bounds
			if (this->dimensions < i + 1)
				values[i] = oldValues[i];
			else
				values[i] = 0.0f;
		}
		this->dimensions = dimensions;
	}
}

void FVector::normalize()
{
	// U = V / |V|
	float sum = 0;
	for (int i = 0; i < dimensions; i++)
		sum += pow(values[i], 2);

	float length = sqrt(sum);
	for (int i = 0; i < dimensions; i++)
		values[i] = values[i] / length;
}

// Overloaded operators
FVector FVector::operator+ (const FVector& v)
{
	if (dimensions != v.getDimensions())
	{
		std::cout << "Illegal Argument: Vectors do not have the same dimensions!" << std::endl;
		return NULL;
	}

	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] + v.getValues()[i];

	return newVector;
}
FVector FVector::operator+ (const float& value)
{
	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] + value;

	return newVector;
}
FVector FVector::operator- (const FVector& v)
{
	if (dimensions != v.getDimensions())
	{
		std::cout << "Illegal Argument: Vectors do not have the same dimensions!" << std::endl;
		return NULL;
	}

	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] - v.getValues()[i];

	return newVector;
}
FVector FVector::operator- (const float& value)
{
	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] - value;

	return newVector;
}
FVector FVector::operator* (const float& value)
{
	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] * value;

	return newVector;
}
FVector FVector::operator/ (const float& value)
{
	FVector newVector(dimensions);
	for (int i = 0; i < dimensions; i++)
		newVector.getValues()[i] = values[i] / value;

	return newVector;
}
FVector& FVector::operator= (const FVector& copy)
{
	dimensions = copy.getDimensions();
	values = new float[dimensions];
	for (int i = 0; i < dimensions; i++)
		values[i] = copy.getValues()[i];

	return *this;
}
bool FVector::operator== (const FVector& v)
{
	if (dimensions != v.getDimensions())
		return false;
	else
	{
		for (int i = 0; i < dimensions; i++)
		{
			if (values[i] != v.getValues()[i])
				return false;
		}
	}

	return true;
}
bool FVector::operator!= (const FVector& v)
{
	return !((*this) == v);
}