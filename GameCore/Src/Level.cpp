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
#include "Level.hpp"

#include <stdexcept>

const std::string Level::difficultyNames[static_cast<int>(Level::Difficulty::Highest) + 1] =
{
	"Easy",
	"Medium",
	"Hard"
};

void Level::Preview::SetElement(Level::Element element, Point2D position)
{
	this->elements[position.GetY() * this->width + position.GetX()] = element;
}

void Level::Preview::SetElement(Level::Element element, int index)
{
	this->elements[index] = element;
}

Level::Preview::Preview(std::string name, const int width, const int height, Element * elements, const Color backgroundColor)
	: name(name), width(width), height(height), size(width * height), backgroundColor(backgroundColor)
{
	for (int i = 0; i < size; ++i)
	{
		switch (elements[i])
		{
			case Element::SnakeFragment:
			case Element::FruitInTail:
			case Element::SnakeHead:
			case Element::SnakeFruitHead:
			{
				throw std::invalid_argument("Level elements cannot contain 'FruitInTail', 'SnakeFragment', 'SnakeHead' or 'SnakeFruitHead'.");
			} break;
			default:
			  break;
		}
	}

	this->elements = new Element[size];
	std::copy(elements, elements + size, this->elements);
}

Level::Preview::Preview(const Preview& preview)
	: name(preview.name), width(preview.width), height(preview.height), size(preview.size), backgroundColor(preview.backgroundColor)
{
	this->elements = new Element[preview.size];
	std::copy(preview.elements, preview.elements + preview.size, this->elements);
}

Level::Preview::~Preview()
{
	delete [] this->elements;
}

std::string Level::Preview::GetName() const
{
	return this->name;
}

int Level::Preview::GetWidth() const
{
	return this->width;
}

int Level::Preview::GetHeight() const
{
	return this->height;
}

int Level::Preview::GetSize() const
{
	return this->size;
}

Level::Element Level::Preview::GetElement(Point2D position) const
{
	return this->elements[position.GetY() * this->width + position.GetX()];
}

Level::Element Level::Preview::GetElement(int index) const
{
	return this->elements[index];
}

Color Level::Preview::GetBackgroundColor() const
{
	return this->backgroundColor;
}

Point2D Level::Move(Point2D position, const Point2D movement) const
{
	position += movement;
	if (0 > position.GetX())
	{
		position.SetX(this->preview.GetWidth() + position.GetX());
	}
	else if (this->preview.GetWidth() - 1 < position.GetX())
	{
		position.SetX(position.GetX() - this->preview.GetWidth());
	}

	if (0 > position.GetY())
	{
		position.SetY(this->preview.GetHeight() + position.GetY());
	}
	else if (this->preview.GetHeight() - 1 < position.GetY())
	{
		position.SetY(position.GetY() - this->preview.GetHeight());
	}

	return position;
}

bool Level::ValidateInput(GameInput input) const
{
	if (!input.IsValid())
	{
		return false;
	}

	Point2D currentSnakeMove = Directions::units[this->snake.GetHead().moveDirection];
	Point2D newSnakeMove = Directions::units[input.GetDirection()];

	if (-currentSnakeMove == newSnakeMove)
	{
		return false;
	}

	return true;
}

void Level::SpawnNewFruits()
{
	this->spawnedFruits.clear();

	this->spawner->SpawnFruits(*this);

	this->numberOfFruits += this->spawnedFruits.size();
}

void Level::SetNewFruits()
{
	for (Fruit const& i : this->spawnedFruits)
	{
		this->preview.SetElement(Element::Fruit, i.position);
	}
}

void Level::RemoveSnakeOldTail()
{
	this->preview.SetElement(Element::Empty, this->snake.GetOldTail().position);
}

void Level::UpdateSnakeTail()
{
	this->preview.SetElement(Element::SnakeFragment, this->snake.GetTail().position);
}

void Level::RemoveSnakeOldHead()
{
	int index = this->snake.GetOldHead().position.GetY() * this->preview.GetWidth() + this->snake.GetOldHead().position.GetX();
	if (Element::SnakeFruitHead == this->preview.GetElement(index))
	{
		this->preview.SetElement(Element::FruitInTail, index);
	}
	else
	{
		this->preview.SetElement(Element::SnakeFragment, index);
	}
}

void Level::UpdateSnakeHead(bool transform)
{
	this->preview.SetElement(transform ? Element::SnakeFruitHead : Element::SnakeHead, this->snake.GetHead().position);
}

void Level::SetSnakeFragments()
{
	SnakeNode node = this->snake.GetHead();
	SnakeNode * nodePtr = &node;
	Point2D fragmentPosition = nodePtr->position;
	this->preview.SetElement(Element::SnakeHead, fragmentPosition);

	while (nullptr != nodePtr)
	{
		Point2D moveUnit = Directions::units[nodePtr->moveDirection];
		nodePtr = nodePtr->next;
		while (nullptr != nodePtr && fragmentPosition != nodePtr->position)
		{
			fragmentPosition = this->Move(fragmentPosition, -moveUnit);
			this->preview.SetElement(Element::SnakeFragment, fragmentPosition);
		}
	}
}

Point2D Level::GetUpdatedPosition(Point2D position, Direction direction) const
{
	return this->Move(position, Directions::units[direction]);
}

Level::Level(Preview& preview, Snake& snake, LevelSpawner& spawner, int frameDurationMs)
	: preview(preview), snake(snake), spawner(&spawner),
	  numberOfFruits(0), numberOfBlocks(0), frameDurationMs(frameDurationMs), lastInput(snake.GetHead().moveDirection, false)
{
	this->spawner->InitSpawner();

	for (int i = 0; i < this->preview.GetSize(); ++i)
	{
		switch (this->preview.GetElement(i))
		{
			case Element::Block:
			{
				++this->numberOfBlocks;
			} break;
			case Element::Fruit:
			{
				++this->numberOfFruits;
			} break;
			default:
			  break;
		}
	}

	this->SetSnakeFragments();
}

Level::~Level()
{ }

const Level::Preview * Level::GetPreview() const
{
	return &this->preview;
}

int Level::GetNumberOfFruits() const
{
	return this->numberOfFruits;
}

int Level::GetNumberOfBlocks() const
{
	return this->numberOfBlocks;
}

int Level::GetNumberOfEmptySpaces() const
{
	return this->preview.GetSize() - this->numberOfBlocks - this->numberOfFruits - this->snake.GetSize();
}

int Level::GetFrameDurationMs() const
{
	return this->frameDurationMs;
}

bool Level::Update(GameInput input)
{
	// Validate input - take last if invalid
	if (!this->ValidateInput(input))
	{
		input = this->lastInput;
	}
	else
	{
		this->lastInput = input;
	}

	// Update swallowed fruits.
	this->snake.UpdateSwallowedFruits();
	// Check if the tail transformation should occur - remove last tail fragment or keep it on the level (transformed into normal tail fragment).
	if (!this->snake.CheckTailTransformation())
	{
		this->snake.MoveTail(this->GetUpdatedPosition(this->snake.GetTail().position, this->snake.GetTail().moveDirection));
		this->RemoveSnakeOldTail();
	}
	else
	{
		this->UpdateSnakeTail();
	}
	/** Check head collision:
	 * - 'block', 'snake fragment' or 'fruit in tail' means game over (return false)
	 * - 'fruit' means snake swallows it
	 * - border means snake's head teleports to the opposite part of the level
	 */
	// Make the update on the level based on the collision.
	Point2D newSnakeHeadPosition = this->GetUpdatedPosition(this->snake.GetHead().position, input.GetDirection());
	Element elementCollided = this->preview.GetElement(newSnakeHeadPosition);
	switch(elementCollided)
	{
		case Element::Block:
		case Element::FruitInTail:
		case Element::SnakeFragment:
		case Element::SnakeHead:
		case Element::SnakeFruitHead:
		{
			return false;
		} break;
		case Element::Fruit:
		{
			this->snake.SwallowFruit(Fruit
			{
				.position = newSnakeHeadPosition
			});
			--this->numberOfFruits;
		} break;
		default:
		  break;
	}
	// Move snake's head.
	this->snake.MoveHead(input.GetDirection(), newSnakeHeadPosition);
	this->RemoveSnakeOldHead();
	this->UpdateSnakeHead(Element::Fruit == elementCollided);

	// Spawn new fruits.
	this->SpawnNewFruits();
	this->SetNewFruits();

	return true;
}
