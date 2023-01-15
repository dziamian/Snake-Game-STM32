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
#ifndef INC_LEVEL_HPP_
#define INC_LEVEL_HPP_

#include <string>

#include "GameInput.hpp"
#include "Helpers.hpp"
#include "Snake.hpp"
#include "Fruit.hpp"
#include "LevelSpawner.hpp"

class LevelSpawner;
class Level
{
	friend class GameRenderer;
	friend class LevelSpawner;

public:
	enum class Element : int
	{
		Empty,
		Block,
		SnakeFragment,
		Fruit,
		FruitInTail,
		SnakeHead,
		SnakeFruitHead,
		Count
	};
	enum class Difficulty : int
	{
		Easy,
		Medium,
		Hard,
		Lowest = Easy,
		Highest = Hard
	};
	static const std::string difficultyNames[static_cast<int>(Difficulty::Highest) + 1];
	class Preview
	{
		friend class Level;

		std::string name;

		const int width;
		const int height;
		const int size;
		Element * elements;
		const Color backgroundColor;

		void SetElement(Element element, Point2D position);
		void SetElement(Element element, int index);

	public:
		Preview(std::string name, const int width, const int height, Element * elements, const Color backgroundColor);
		Preview(const Preview& preview);
		Preview& operator = (const Preview& preview) = delete;
		~Preview();
		std::string GetName() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetSize() const;
		Element GetElement(Point2D position) const;
		Element GetElement(int index) const;
		Color GetBackgroundColor() const;
	};

private:
	Preview preview;
	Snake snake;
	LevelSpawner * spawner;
	std::list<Fruit> spawnedFruits;

	int numberOfFruits;
	int numberOfBlocks;

	int frameDurationMs;
	GameInput lastInput;

	Point2D Move(Point2D position, const Point2D movement) const;
	bool ValidateInput(GameInput input) const;

	void SpawnNewFruits();
	void SetNewFruits();
	void RemoveSnakeOldTail();
	void UpdateSnakeTail();
	void RemoveSnakeOldHead();
	void UpdateSnakeHead(bool transform);
	void SetSnakeFragments();
	Point2D GetUpdatedPosition(Point2D position, Direction direction) const;

public:
	Level(Preview& preview, Snake& snake, LevelSpawner& spawner, int frameDurationMs);
	Level(const Level& level) = default;
	Level& operator = (const Level& level) = delete;
	~Level();
	const Preview * GetPreview() const;
	int GetNumberOfFruits() const;
	int GetNumberOfBlocks() const;
	int GetNumberOfEmptySpaces() const;
	int GetFrameDurationMs() const;

	bool Update(GameInput input);
};

#endif /* INC_LEVEL_HPP_ */
