/*
 * miniMath.c
 *
 *  Created on: Apr 19, 2012
 *      Author: ACM
 */

#include "miniMath.h"

uint m_w = 25;    /* must not be zero */
uint m_z = 683;    /* must not be zero */

uint randNum()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

double sin(double angle)
{
	while (angle>=6.28318)
		angle-=6.28318;
	double xSquared = angle*angle;
	double x = angle;
	double ans = x;
	u8 posOrNeg = 0;
	u16 lcv = 0;
	double fact = 1;
	for (lcv = 3;lcv<26;lcv=lcv+2)
	{
		fact *= (lcv*(lcv-1));
		x *= ((xSquared)/(lcv*(lcv-1)));

		if (posOrNeg == 0)
			ans -= x;
		else
			ans += x;

		posOrNeg = 1-posOrNeg;
	}
	return (ans);
}

//double sin(int angle)
//{
//	double lTable[] = {0,0.17364817766693,0.342020143325669,0.5,0.642787609686539,0.766044443118978,0.866025403784439,0.939692620785908,0.984807753012208,1,0.984807753012208,0.939692620785908,0.866025403784439,0.766044443118978,0.642787609686539,0.5,0.342020143325669,0.17364817766693,0};
//
//	while (angle>=360)
//		angle-=360;
//
//	if (angle<180)
//		return lTable[(angle/10)];
//	else
//		return -1*lTable[(angle/10)];
//}

double cos(double angle)
{
	return sin(angle+3.14159/2);
}
