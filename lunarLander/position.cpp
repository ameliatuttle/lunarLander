/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Amelia Tuttle
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
// I declared this in the other .h file with the other constructors
// Position::Position(double x, double y) : x(x), y(y) { }

/******************************************
 * POINT : ADD
 * Update point based on the distance formula
 *   s = s_0 + vt + 1/2 a t^2
 *****************************************/
void Position::add(const Acceleration & a, const Velocity & v, double t)
{
    // Calculate changes
    double dx = v.getDX() * t + 0.5 * a.getDDX() * t * t;
    double dy = v.getDY() * t + 0.5 * a.getDDY() * t * t;
    
    // Add changes to the existing position
    x += dx;
    y += dy;
}
