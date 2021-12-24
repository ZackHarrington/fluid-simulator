#include "Particle2D.h"

float* Particle2D::generateOpenGLVertices(unsigned int resolution, bool includeColor, unsigned int* vertexDataSize,
	bool includeIndices, unsigned int* indicesSize, unsigned int** indices)
{
	unsigned int resolutionToUse = resolution;
	if (resolution < 3) {
		std::cout << "Illegal Argument: Resolution must be three or greater!" << std::endl;
		resolutionToUse = 3;
	}

	// The circles are sliced up like a pie where each slice cooresponds to a triangle
	float* vertexData = nullptr;
	float radiansPerSlice = (2 * 3.14159265) / resolutionToUse;	// 2pi/resolution
	if (includeIndices)
	{
		// With indices we only need to specify the center and each of the outer points around the 'circle'
		// Then, with indices, we can specify how to draw each pie slice
		// (center + each outer point) * 3 because they are 3D vectors (z filled with 0)
		// The last part says if we are including color information we'll need an additional 3D vector per point for RGB information
		float numVertices = (1 + resolutionToUse);
		float numFloats = numVertices * 3 * (includeColor ? 2 : 1);
		*vertexDataSize = numFloats;							// assign vertexDataSize variable
		vertexData = new float[numFloats];

		// Add center vertex
		vertexData[0] = position.getValues()[0];				// x
		vertexData[1] = position.getValues()[1];				// y
		vertexData[2] = 0.0f;									// z
		if (includeColor)
		{
			vertexData[3] = color.getValues()[0];				// R
			vertexData[4] = color.getValues()[1];				// G
			vertexData[5] = color.getValues()[2];				// B
		}

		// Fill vertices loop
		for (int i = 1; i <= resolutionToUse; i++)				// start at 1 because we already added the center
		{
			vertexData[6 * i]	  = position.getValues()[0] + radius * cos(radiansPerSlice * (i - 1));
			vertexData[6 * i + 1] = position.getValues()[1] + radius * sin(radiansPerSlice * (i - 1));
			vertexData[6 * i + 2] = 0.0f;
			if (includeColor)
			{
				vertexData[6 * i + 3] = color.getValues()[0];
				vertexData[6 * i + 4] = color.getValues()[1];
				vertexData[6 * i + 5] = color.getValues()[2];
			}
		}

		// Fill indices loop
		*indicesSize = resolutionToUse * 3;						// three points per triangle, assign indicesSize variable
		*indices = new unsigned int[*indicesSize];
		for (int i = 0; i < resolutionToUse; i++)
		{
			(*indices)[3 * i] = 0;								// center
			(*indices)[3 * i + 1] = 1 + i;						// first outer vertex
			if (i < resolutionToUse - 1)
				(*indices)[3 * i + 2] = 2 + i;					// second outer vertex
			else
				(*indices)[3 * i + 2] = 1;						// made it around the circle
		}
	}
	else
	{
		// Without indices we have to specify each pie slice individually with three points
		float numVertices = (3 * resolutionToUse);
		float numFloats = numVertices * 3 * (includeColor ? 2 : 1);
		*vertexDataSize = numFloats;							// assign vertexDataSize variable
		vertexData = new float[numFloats];

		// Fill vertices loop
		int index = 0;
		for (int i = 0; i < resolutionToUse; i++)				// each triangle
		{
			for (int j = 0; j < 3; j++)							// each vertex
			{
				if (includeColor)
					index = 18 * i + 6 * j;
				else
					index = 9 * i + 3 * j;

				switch (j)
				{
				case 0:											// first vertex is the center
					vertexData[index]     = position.getValues()[0];
					vertexData[index + 1] = position.getValues()[1];
					vertexData[index + 2] = 0.0f;
					break;
				case 1:											// second is the first outer vertex
					vertexData[index]     = position.getValues()[0] + radius * cos(radiansPerSlice * i);
					vertexData[index + 1] = position.getValues()[1] + radius * sin(radiansPerSlice * i);
					vertexData[index + 2] = 0.0f;
					break;
				case 2:											// third is the second outer vertex
					vertexData[index]     = position.getValues()[0] + radius * cos(radiansPerSlice * (i + 1));
					vertexData[index + 1] = position.getValues()[1] + radius * sin(radiansPerSlice * (i + 1));
					vertexData[index + 2] = 0.0f;
					break;
				}
				if (includeColor)
				{
					vertexData[index + 3] = color.getValues()[0];
					vertexData[index + 4] = color.getValues()[1];
					vertexData[index + 5] = color.getValues()[2];
				}
			}
		}
	}

	return vertexData;
}

// Overloaded operators
bool Particle2D::operator== (const Particle2D& p)
{
	return (radius == p.getRadius()) &&
		(mass == p.getMass()) &&
		(position == p.getPosition()) &&
		(velocity == p.getVelocity()) &&
		(color == p.getColor());
}
bool Particle2D::operator!= (const Particle2D& p)
{
	return !((*this) == p);
}