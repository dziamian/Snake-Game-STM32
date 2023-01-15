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
#ifndef INC_LEVELSPAWNER_HPP_
#define INC_LEVELSPAWNER_HPP_

#include "Level.hpp"

class Level;
class LevelSpawner
{
protected:
	Point2D GetEmptySpace(Level& level, int coordinates) const;
	void AddSpawnedFruit(Level& level, Fruit fruit) const;

public:
	virtual void InitSpawner() = 0;
	virtual void SpawnFruits(Level& level) = 0;
	virtual ~LevelSpawner() = default;
};

class NormalLevelSpawner : public LevelSpawner
{
	const int tilesPerFruit;

public:
	NormalLevelSpawner(const int tilesPerFruit);
	~NormalLevelSpawner();
	void InitSpawner();
	void SpawnFruits(Level& level);
};

#endif /* INC_LEVELSPAWNER_HPP_ */
