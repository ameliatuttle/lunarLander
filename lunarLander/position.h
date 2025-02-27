/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Amelia Tuttle
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once


class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests
class TestLander;      // for the unit tests

/*********************************************
 * POSITION
 * A single position on the screen
 *********************************************/
class Position
{
   friend TestPosition;    // for the unit tests
   friend TestLander;      // for the unit tests
   
public:
   // Default constructor
   Position() : x(0.0), y(0.0) { }
    
    // Non-default constructor
   Position(double x, double y) : x(x), y(y) { }
    
    // Copy constructor
    Position(const Position &pos) : x(pos.x), y(pos.y) { }

   // getters
   double getX() const { return x; }
   double getY() const { return y; }
    
    // Equals boolean
   bool operator == (const Position &rhs) const
   {
      return x == rhs.x && y == rhs.y;
   }
    
    // Not equals boolean
   bool operator != (const Position &rhs) const
   {
      return !(*this == rhs);
   }

   // setters
   void setX(double x) { this->x = x; }
   void setY(double y) { this->y = y; }
   void addX(double x) { this->x += x; }
   void addY(double y) { this->y += y; }
   void add (const Acceleration & a, const Velocity & v, double t);
    
   Position & operator = (const Position &rhs)
   {
       if (this != &rhs) {
           x = rhs.x;
           y = rhs.y;
       }
      return *this;
   }

private:
   double x;           // horizontal position
   double y;           // vertical position
};
