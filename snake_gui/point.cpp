/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
# Project4: Snake                                                  #
####################################################################
*
* This is a implementation file where is all Point class method
* implementations.
*
* I have only implemented getX() and getY() methods.
*
* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
* */


#include "point.hh"
#include <iostream>

Point::Point() : x_(0), y_(0)
{
}

Point::Point(int x, int y) :
    x_(x), y_(y)
{
}

Point::~Point()
{
}

bool Point::operator==(const Point &rhs) const
{
    return x_ == rhs.x_ and y_ == rhs.y_;
}

bool Point::operator!=(const Point &rhs) const
{
    return x_ != rhs.x_ or y_ != rhs.y_;
}

void Point::setPosition(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Point::move(const std::string &dir)
{
    if(dir.size() != 1)
    {
        std::cout << "Internal error: impossible direction" << std::endl;
        return;
    }
    switch(dir.at(0))
    {
        case UP: --y_; break;
        case LEFT: --x_; break;
        case DOWN: ++y_; break;
        case RIGHT: ++x_; break;
        default: std::cout << "Internal error: impossible direction"
                           << std::endl;
    }
}

bool Point::isInside(int left_top_x, int left_top_y,
                     int right_bottom_x, int right_bottom_y) const
{
    return (x_ >= left_top_x) and (y_ >= left_top_y) and
            (x_ <= right_bottom_x) and (y_ <= right_bottom_y);
}

int Point::getX()
{
    //Returns points x-coordinate which is stored to attribute x_
    return x_;
}

int Point::getY()
{
    //Returns points y-coordinate which is stored to attribute y_
    return y_;
}

