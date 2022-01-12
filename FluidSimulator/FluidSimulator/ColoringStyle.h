#pragma once

#ifndef COLORINGSTYLE_H
#define COLORINGSTYLE_H

enum class ColoringStyle
{
	DEFAULT_WHITE,							// All particles are white
	DEFAULT_FACTORY,						// Color is defined by the particleFactory
	SPEED_BLUE,								// All particles are blue, color gets lighter the faster the particle is moving
	SPEED_FACTORY							// Color defined by the particleFactory, gets lighter the faster the particle is moving
};

#endif