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
#ifndef INC_HELPERS_HPP_
#define INC_HELPERS_HPP_

#include <stdint.h>

class Point2D
{
private:
	int x;
	int y;

public:
	constexpr Point2D(const int x, const int y)
		: x(x), y(y)
	{ }

	int GetX() const;
	void SetX(const int x);
	int GetY() const;
	void SetY(const int y);
	Point2D GetUnit() const;

	Point2D operator - () const;
	Point2D operator - (const Point2D& point) const;
	Point2D& operator -= (const Point2D& point);
	Point2D operator + (const Point2D& point) const;
	Point2D& operator += (const Point2D& point);
	bool operator == (const Point2D& point) const;
	bool operator != (const Point2D& point) const;
};

enum Direction
{
	Up,
	Down,
	Left,
	Right,
	Invalid
};

class Directions
{
public:
	static constexpr Point2D units[] =
	{
		[Direction::Up] = Point2D(0, 1),
		[Direction::Down] = Point2D(0, -1),
		[Direction::Left] = Point2D(-1, 0),
		[Direction::Right] = Point2D(1, 0)
	};
	static constexpr int amount = sizeof(Directions::units) / sizeof(Directions::units[0]);

	static Direction GetDirection(const Point2D& point);
	static Direction ReverseX(const Direction direction);
	static Direction ReverseY(const Direction direction);
	static Direction ReverseAxes(const Direction direction);
};

class Color
{
	const uint16_t rgb565;

public:
	constexpr Color(const uint16_t rgb565)
		: rgb565(rgb565)
	{ }

	constexpr uint16_t GetRgb565() const
	{
		return this->rgb565;
	}
};

class Colors
{
public:
	static constexpr Color Red 		= Color(0xF800);
	static constexpr Color Green	= Color(0x07E0);
	static constexpr Color Blue		= Color(0x001F);
	static constexpr Color Black	= Color(0x0000);
	static constexpr Color White	= Color(0xFFFF);
};

#endif /* INC_HELPERS_HPP_ */
