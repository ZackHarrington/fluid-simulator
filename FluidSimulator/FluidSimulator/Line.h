#pragma once

#ifndef LINE_H
#define LINE_H

#include "FVector.h"

#include <iostream>
#include <math.h>

class Line
{
public:
	/* Description: Default constructor for a line of zero length in three dimensions
	 */
	Line();
	/* Description: Initializes a line based on two positions
	 * Parameters: positions should have the same dimensions
	 */
	Line(FVector position1, FVector position2, const FVector color);
	/* Description: Copy constructor
	 */
	Line(const Line& copy);
	/* Description: Default destructor
	 */
	~Line();

	// Getters / setters
	/* Description: Returns the line's start position as a float vector
	 */
	FVector getPosition1() const;
	/* Description: Returns the line's end position as a float vector
	 */
	FVector getPosition2() const;
	/* Description: Returns the line's directional vector as a float vector
	 */
	FVector getDirection() const;
	/* Description: Returns the line's color as a float vector
	 */
	FVector getColor() const;
	/* Description: Returns the line's midpoint as a float vector
	 */
	FVector getMidpoint() const;
	/* Description: Returns the length of the line
	 */
	float getLength() const;
	/* Description: Sets the line's start position as a float vector
	 * Parameters: position should have the same dimensions as the end position
	 */
	void setPosition1(FVector position1);
	/* Description: Sets the line's end position as a float vector
	 * Parameters: position should have the same dimensions as the start position
	 */
	void setPosition2(FVector position2);
	/* Description: Sets the line's start and end position as a float vector
	 * Parameters: positions should have the same dimensions
	 */
	void setPosition(FVector position1, FVector position2);
	/* Description: Sets the line's color as a float vector
	 */
	void setColor(const FVector color);

	// Overloaded operators
	Line& operator= (const Line& copy);
	bool operator== (const Line& l);
	bool operator!= (const Line& l);
private:
	FVector position1;
	FVector position2;
	FVector direction;		// Unit vector, points from position1 towards position2
	FVector color;

	/* Description: Calculates the line's directional vector from the two positions
	 */
	void calculateDirection();
};


#endif
