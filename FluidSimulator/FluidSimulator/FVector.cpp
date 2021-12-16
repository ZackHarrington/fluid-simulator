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
FVector::FVector(const FVector& copyVector)
{
	dimensions = copyVector.getDimensions();
	values = new float[dimensions];
	for (int i = 0; i < dimensions; i++)
		values[i] = copyVector.getValues()[i];
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

// Overloaded operator
FVector& FVector::operator= (const FVector& copyVector)
{
	dimensions = copyVector.getDimensions();
	values = new float[dimensions];
	for (int i = 0; i < dimensions; i++)
		values[i] = copyVector.getValues()[i];

	return *this;
}


/* Non-Member Functions */
// Overloaded operators - need to be pass by reference
FVector operator+ (const FVector& v1, const FVector& v2)
{
	if (v1.getDimensions() != v2.getDimensions())
		std::cout << "Illegal Argument: Vectors do not have the same dimensions" << std::endl;

	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] + v2.getValues()[i];

	return newVector;
}
FVector operator+ (const FVector& v1, const float& value)
{
	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] + value;

	return newVector;
}
FVector operator- (const FVector& v1, const FVector& v2)
{
	if (v1.getDimensions() != v2.getDimensions())
		std::cout << "Illegal Argument: Vectors do not have the same dimensions" << std::endl;

	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] - v2.getValues()[i];

	return newVector;
}
FVector operator- (const FVector& v1, const float& value)
{
	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] - value;

	return newVector;
}
FVector operator* (const FVector& v1, const float& value)
{
	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] * value;

	return newVector;
}
FVector operator/ (const FVector& v1, const float& value)
{
	FVector newVector(v1.getDimensions());
	for (int i = 0; i < newVector.getDimensions(); i++)
		newVector.getValues()[i] = v1.getValues()[i] / value;

	return newVector;
}