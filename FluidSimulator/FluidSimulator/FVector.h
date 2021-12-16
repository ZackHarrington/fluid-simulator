#pragma once

#ifndef FVECTOR_H
#define FVECTOR_H

#include <iostream>
#include <math.h>

class FVector
{
public:
	/* Description: Creates a N dimentional vector of the float type
	 * Parameters: There should be the same number of values as there are dimensions
	 *				Defaults to a 3 dimensional zero-vector
	 */
	FVector(unsigned int dimensions = 3U, float* values = nullptr);
	/* Discription: FVector copy constructor
	 */
	FVector(const FVector& copyVector);
	/* Description: Deallocates space once vector is no longer needed
	 */
	~FVector();

	// Getters / setters
	/* Description: Returns the dimensions of the vector
	 */
	unsigned int getDimensions() const;
	/* Description: Returns the values of the vector
	 */
	float* getValues() const;
	/* Description: Sets the dimensions of the vector
	 * Warning: Will delete values if specified dimensions are lower than current dimensions!
	 * Warning: Will add 0 values if specified dimensions are higher than current dimensions!
	 */
	void setDimensions(unsigned int dimensions);

	/* Description: Normalizes the vector
	 */
	void normalize();

	// Overloaded operator
	FVector& operator= (const FVector& copyVector);

private:
	unsigned int dimensions;
	float* values;
};

// Overloaded operators - need to be pass by reference
FVector operator+ (const FVector& v1, const FVector& v2);
FVector operator+ (const FVector& v1, const float& value);
FVector operator- (const FVector& v1, const FVector& v2);
FVector operator- (const FVector& v1, const float& value);
FVector operator* (const FVector& v1, const float& value);
FVector operator/ (const FVector& v1, const float& value);


#endif