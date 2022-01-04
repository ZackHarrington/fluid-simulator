#pragma once

#ifndef FVECTOR_H
#define FVECTOR_H

// OpenGL Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
// Cpp includes
#include <iostream>
#include <math.h>

class FVector
{
public:
	/* Description: Creates a N dimentional vector of the float type
	 * Parameters: There should be the same number of values as there are dimensions
	 *				Defaults to a 3 dimensional zero-vector
	 */
	FVector(const unsigned int dimensions = 3U, const float* values = nullptr);
	/* Discription: FVector copy constructor
	 */
	FVector(const FVector& copy);
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
	/* Description: Returns the length of the vector
	 */
	float getLength() const;
	/* Description: Returns the distance from another FVector
	 * Warning: If the vectors don't have the same dimensions the distance will be reported in this->dimensions
	 */
	float getDistance(const FVector& v) const;
	/* Description: Sets the dimensions of the vector
	 * Warning: Will delete values if specified dimensions are lower than current dimensions!
	 * Warning: Will add 0 values if specified dimensions are higher than current dimensions!
	 */
	void setDimensions(const unsigned int dimensions);

	/* Description: Returns the float vector as a glm::vec2, will add 0.0f values when dimensions are smaller than 2
	 * Warning: May not be able to report all dimensions if there are more than 2!
	 */
	glm::vec2 toGLMvec2() const;
	/* Description: Returns the float vector as a glm::vec3, will add 0.0f values when dimensions are smaller than 3
	 * Warning: May not be able to report all dimensions if there are more than 3!
	 */
	glm::vec3 toGLMvec3() const;
	/* Description: Returns the float vector as a glm::vec4, will add 0.0f values when dimensions are smaller than 4
	 * Warning: May not be able to report all dimensions if there are more than 4!
	 */
	glm::vec4 toGLMvec4() const;

	/* Description: Normalizes the vector
	 */
	void normalize();

	// Overloaded operators - need to be pass by reference
	FVector operator+ (const FVector& v);
	FVector operator+ (const float& value);
	FVector operator- (const FVector& v);
	FVector operator- (const float& value);
	float operator* (const FVector& v);		// Acts like the dot product
	FVector operator* (const float& value);
	FVector operator/ (const float& value);
	FVector& operator= (const FVector& copy);
	bool operator== (const FVector& v);
	bool operator!= (const FVector& v);
private:
	unsigned int dimensions;
	float* values;
};


#endif