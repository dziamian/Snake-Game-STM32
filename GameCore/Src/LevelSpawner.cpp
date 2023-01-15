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
#include "LevelSpawner.hpp"

#include <time.h>

Point2D LevelSpawner::GetEmptySpace(Level& level, int coordinates) const
{
	for (int i = 0; i < level.preview.GetSize(); ++i)
	{
		if ((Level::Element::Empty == level.preview.GetElement(i)) && (0 == coordinates--))
		{
			return Point2D(i % level.preview.GetWidth(), i / level.preview.GetWidth());
		}
	}

	return Point2D(-1, -1);
}

void LevelSpawner::AddSpawnedFruit(Level& level, Fruit fruit) const
{
	level.spawnedFruits.push_back(fruit);
}

NormalLevelSpawner::NormalLevelSpawner(const int tilesPerFruit)
	: tilesPerFruit(tilesPerFruit)
{ }

NormalLevelSpawner::~NormalLevelSpawner()
{ }

void NormalLevelSpawner::InitSpawner()
{
	srand(time(NULL));
}

void NormalLevelSpawner::SpawnFruits(Level& level)
{
	const int numberOfEmptySpaces = level.GetNumberOfEmptySpaces();
	int expectedNumberOfFruits = numberOfEmptySpaces / this->tilesPerFruit;
	if (0 == expectedNumberOfFruits)
	{
		++expectedNumberOfFruits;
	}
	const int numberOfFruitsToSpawn = expectedNumberOfFruits - level.GetNumberOfFruits();

	for (int i = 0; i < numberOfFruitsToSpawn; ++i)
	{
		this->AddSpawnedFruit(level, Fruit
		{
			.position = this->GetEmptySpace(level, rand() % numberOfEmptySpaces)
		});
	}
}
