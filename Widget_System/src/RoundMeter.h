/*
 * RoundMeter.h
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 */

#ifndef ROUNDMETER_H_
#define ROUNDMETER_H_

#include "Widget.h"
#include "Graphics.h"
#include <math.h>

class RoundMeter : public Widget
{
public:
	double angle;
	RoundMeter(int x, int y, double angle);
	void draw();
};

#endif /* ROUNDMETER_H_ */