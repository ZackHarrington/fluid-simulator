#pragma once

#ifndef COLORINGSTYLE_H
#define COLORINGSTYLE_H

enum class ColoringStyle
{
	DEFAULT_WHITE,							// All particles are white
	DEFAULT_FACTORY,						// Color is defined by the particleFactory
	SPEED_BLUE,								// Color gets lighter the faster the particle is moving
	SPEED_FACTORY							// Color defined by the particleFactory, made lighter or darker based on the particle's speed
};

#endif