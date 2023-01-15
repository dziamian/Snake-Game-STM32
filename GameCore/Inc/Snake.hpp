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
#ifndef INC_SNAKE_HPP_
#define INC_SNAKE_HPP_

#include <list>

#include "Fruit.hpp"
#include "Helpers.hpp"

struct SnakeNode
{
	Point2D position;
	Direction moveDirection;
	SnakeNode * next;
};

class Snake
{
private:
	SnakeNode * head;
	SnakeNode * tail;
	SnakeNode * oldHead;
	SnakeNode * oldTail;
	int size;
	std::list<SwallowedFruit> swallowedFruits;
	bool tailTransformation;

public:
	Snake(Point2D headPosition, Point2D tailPosition);
	Snake(const Snake& snake);
	Snake& operator = (const Snake& snake) = delete;
	~Snake();
	SnakeNode GetHead() const;
	SnakeNode GetTail() const;
	SnakeNode GetOldHead() const;
	SnakeNode GetOldTail() const;
	int GetSize() const;
	bool CheckTailTransformation() const;

	void MoveHead(Direction newDirection, Point2D newPosition);
	void MoveTail(Point2D newPosition);
	void SwallowFruit(Fruit fruit);
	void UpdateSwallowedFruits();
};

#endif /* INC_SNAKE_HPP_ */
