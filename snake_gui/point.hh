/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
# Project4: Snake                                                  #
####################################################################
*This class was base code to this project snake. I have only added this class
*public methods getX() and getY(). The rest methods was already
*implemented.
*
*This is a header file to Point class. Point class takes care of how
*snake parts coordinates changes. It also tells is snake colliding to game areas
*wall. Classes methods and attributes are indroduced in this file and you can
*read more details above method or attribute in guestion.
*
* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*
*/

#ifndef POINT_HH
#define POINT_HH

#include <string>

// Constants for directions
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';

class Point
{
public:
    // Default constructor, creates a new point at (0, 0).
    Point();

    // Constructor, creates a new point at the given coordinates.
    Point(int x, int y);

    // Destructor
    ~Point();

    // Comparison operators
    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    // Sets a new position for the point
    void setPosition(int x, int y);

    // Moves the point into the given direction, direction can be one of
    // constants above.
    void move(const std::string& dir);

    // Tells if the point is inside the square specified by the given
    // parameters.
    bool isInside(int left_top_x, int left_top_y,
                  int right_bottom_x, int right_bottom_y) const;
    //Gets point's x-coordinate
    int getX();

    //Gets point's y-coordinate
    int getY();
private:
    // Coordinates of the point
    int x_;
    int y_;
    const int STEP = 20;
};

#endif // POINT_HH
