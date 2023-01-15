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
#include "Snake.hpp"

#include <stdexcept>
#include <cmath>

Snake::Snake(Point2D headPosition, Point2D tailPosition)
	: tailTransformation(false)
{
	Direction moveDirection = Directions::GetDirection(headPosition - tailPosition);
	if (Direction::Invalid == moveDirection)
	{
		throw std::invalid_argument("Wrong head and tail positions. They must lie on one axis.");
	}

	this->tail = new SnakeNode
	{
		.position 		= tailPosition,
		.moveDirection 	= moveDirection,
		.next 			= nullptr
	};
	this->oldTail = new SnakeNode
	{
		.position 		= tailPosition,
		.moveDirection 	= moveDirection,
		.next 			= nullptr
	};
	this->head = new SnakeNode
	{
		.position 		= headPosition,
		.moveDirection 	= moveDirection,
		.next 			= this->tail
	};
	this->oldHead = new SnakeNode
	{
		.position 		= headPosition,
		.moveDirection 	= moveDirection,
		.next 			= nullptr
	};

	Point2D snakeVector = headPosition - tailPosition;
	this->size = std::abs(snakeVector.GetX()) + std::abs(snakeVector.GetY()) + 1;
}

Snake::Snake(const Snake& snake)
	: tailTransformation(snake.tailTransformation)
{
	this->head = new SnakeNode(*snake.head);
	this->tail = new SnakeNode(*snake.tail);
	this->oldHead = new SnakeNode(*snake.oldHead);
	this->oldTail = new SnakeNode(*snake.oldTail);
	this->size = snake.size;
	this->swallowedFruits = snake.swallowedFruits;

	SnakeNode ** nextNode = &this->head->next;
	while (snake.tail != *nextNode)
	{
		*nextNode = new SnakeNode(**nextNode);
		*nextNode = (*nextNode)->next;
	}
	*nextNode = this->tail;
}

Snake::~Snake()
{
	SnakeNode * node = this->head;
	SnakeNode * nextNode;
	while (nullptr != node)
	{
		nextNode = node->next;
		delete node;
		node = nextNode;
	}
	delete this->oldTail;
}

SnakeNode Snake::GetHead() const
{
	return *this->head;
}

SnakeNode Snake::GetTail() const
{
	return *this->tail;
}

SnakeNode Snake::GetOldHead() const
{
	return *this->oldHead;
}

SnakeNode Snake::GetOldTail() const
{
	return *this->oldTail;
}

int Snake::GetSize() const
{
	return this->size;
}

bool Snake::CheckTailTransformation() const
{
	return this->tailTransformation;
}

void Snake::MoveHead(Direction newDirection, Point2D newPosition)
{
	this->oldHead->position = this->head->position;
	this->oldHead->moveDirection = this->oldHead->moveDirection;

	if (this->head->moveDirection != newDirection)
	{
		this->head->next = new SnakeNode
		{
			.position 		= this->head->position,
			.moveDirection 	= newDirection,
			.next 			= this->head->next
		};
	}

	this->head->position = newPosition;
	this->head->moveDirection = newDirection;

	// Clear flag
	this->tailTransformation = false;
}

void Snake::MoveTail(Point2D newPosition)
{
	this->oldTail->position = this->tail->position;
	this->oldTail->moveDirection = this->tail->moveDirection;

	this->tail->position = newPosition;

	SnakeNode * nodeBeforeTail = this->head;
	while (nodeBeforeTail->next != this->tail)
	{
		nodeBeforeTail = nodeBeforeTail->next;
	}

	if (nodeBeforeTail->position == this->tail->position)
	{
		nodeBeforeTail->next = nullptr;
		delete this->tail;
		this->tail = nodeBeforeTail;
	}
}

void Snake::SwallowFruit(Fruit fruit)
{
	// First swallowed fruit will be always in the front of the list.
	this->swallowedFruits.push_back(SwallowedFruit {
		.fruit = fruit,
		.turnsToTailTransformation = this->size
	});
}

void Snake::UpdateSwallowedFruits()
{
	for (std::list<SwallowedFruit>::iterator it = this->swallowedFruits.begin(); it != this->swallowedFruits.end(); ++it)
	{
		if (0 == --it->turnsToTailTransformation)
		{
			this->swallowedFruits.erase(it);
			this->tailTransformation = true;
			++this->size;

			return;
		}
	}
}
