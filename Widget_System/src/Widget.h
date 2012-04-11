/*
 * Widget.h
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 */

#ifndef WIDGET_H_
#define WIDGET_H_


class Widget
{
	public:
		int x, y;
		Widget(int x, int y);
		~Widget();
		virtual void draw() = 0;

};


#endif /* WIDGET_H_ */