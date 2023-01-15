/*
 * MIT License
 *
 * Copyright (c) 2023 Damian Ślusarczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include "Helpers.hpp"

int Point2D::GetX() const
{
	return this->x;
}

void Point2D::SetX(const int x)
{
	this->x = x;
}

int Point2D::GetY() const
{
	return this->y;
}

void Point2D::SetY(const int y)
{
	this->y = y;
}

Point2D Point2D::GetUnit() const
{
	return Point2D((0 < this->x) - (0 > this->x), (0 < this->y) - (0 > this->y));
}

Point2D Point2D::operator - () const
{
	return Point2D(-this->x, -this->y);
}

Point2D Point2D::operator - (const Point2D& point) const
{
	return Point2D(this->x - point.GetX(), this->y - point.GetY());
}

Point2D& Point2D::operator -= (const Point2D& point)
{
	this->x -= point.GetX();
	this->y -= point.GetY();
	return *this;
}

Point2D Point2D::operator + (const Point2D& point) const
{
	return Point2D(this->x + point.GetX(), this->y + point.GetY());
}

Point2D& Point2D::operator += (const Point2D& point)
{
	this->x += point.GetX();
	this->y += point.GetY();
	return *this;
}

bool Point2D::operator == (const Point2D& point) const
{
	return (this->GetX() == point.GetX() &&
			this->GetY() == point.GetY());
}

bool Point2D::operator != (const Point2D& point) const
{
	return (this->GetX() != point.GetX() ||
			this->GetY() != point.GetY());
}

constexpr Point2D Directions::units[];

Direction Directions::GetDirection(const Point2D& point)
{
	Point2D unit = point.GetUnit();
	for (int i = 0; i < Directions::amount; ++i)
	{
		if (Directions::units[i] == unit)
		{
			return static_cast<Direction>(i);
		}
	}

	return Direction::Invalid;
}

Direction Directions::ReverseX(const Direction direction)
{
	switch (direction)
	{
		case Direction::Left:
			return Direction::Right;
		case Direction::Right:
			return Direction::Left;
		case Direction::Up:
		case Direction::Down:
		default:
			return direction;
	}
}

Direction Directions::ReverseY(const Direction direction)
{
	switch (direction)
	{
		case Direction::Up:
			return Direction::Down;
		case Direction::Down:
			return Direction::Up;
		case Direction::Left:
		case Direction::Right:
		default:
			return direction;
	}
}

Direction Directions::ReverseAxes(const Direction direction)
{
	switch (direction)
	{
		case Direction::Up:
			return Direction::Right;
		case Direction::Down:
			return Direction::Left;
		case Direction::Right:
			return Direction::Up;
		case Direction::Left:
			return Direction::Down;
		default:
			return direction;
	}
}

constexpr Color Colors::Red;
constexpr Color Colors::Green;
constexpr Color Colors::Blue;
constexpr Color Colors::Black;
constexpr Color Colors::White;
