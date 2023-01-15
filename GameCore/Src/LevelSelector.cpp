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
#include "LevelSelector.hpp"

void LevelSelector::LoadLevel1(Level::Difficulty difficulty)
{
	Level::Preview preview = this->GetLevel1Preview();
	Snake snake = Snake(Point2D(1, 3), Point2D(1, 1));
	constexpr int frameDurationMs = 1000;

	this->loadedLevelSpawner = new NormalLevelSpawner(20);
	this->loadedLevel = new Level(preview, snake, *this->loadedLevelSpawner, frameDurationMs);
}

Level::Preview LevelSelector::GetLevel1Preview() const
{
	std::string name = "Level 1";
	constexpr int width = 7;
	constexpr int height = 7;
	Level::Element elements[] =
	{
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
	};
	constexpr Color backgroundColor = Colors::Black;

	return Level::Preview(name, width, height, elements, backgroundColor);
}

void LevelSelector::LoadLevel2(Level::Difficulty difficulty)
{
	Level::Preview preview = this->GetLevel2Preview();
	Snake snake = Snake(Point2D(1, 3), Point2D(1, 1));
	constexpr int frameDurationMs = 1000;

	this->loadedLevelSpawner = new NormalLevelSpawner(20);
	this->loadedLevel = new Level(preview, snake, *this->loadedLevelSpawner, frameDurationMs);
}

Level::Preview LevelSelector::GetLevel2Preview() const
{
	std::string name = "Level 2";
	constexpr int width = 9;
	constexpr int height = 9;
	Level::Element elements[] =
	{
		Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Block,
	};
	constexpr Color backgroundColor = Colors::Black;

	return Level::Preview(name, width, height, elements, backgroundColor);
}

void LevelSelector::LoadLevel3(Level::Difficulty difficulty)
{
	Level::Preview preview = this->GetLevel3Preview();
	Snake snake = Snake(Point2D(0, 3), Point2D(0, 1));
	constexpr int frameDurationMs = 1000;

	this->loadedLevelSpawner = new NormalLevelSpawner(20);
	this->loadedLevel = new Level(preview, snake, *this->loadedLevelSpawner, frameDurationMs);
}

Level::Preview LevelSelector::GetLevel3Preview() const
{
	std::string name = "Level 3";
	constexpr int width = 7;
	constexpr int height = 7;
	Level::Element elements[] =
	{
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty,
		Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty,
	};
	constexpr Color backgroundColor = Colors::Blue;

	return Level::Preview(name, width, height, elements, backgroundColor);
}


void LevelSelector::LoadLevel4(Level::Difficulty difficulty)
{
	Level::Preview preview = this->GetLevel4Preview();
	Snake snake = Snake(Point2D(1, 3), Point2D(1, 1));
	constexpr int frameDurationMs = 1000;

	this->loadedLevelSpawner = new NormalLevelSpawner(20);
	this->loadedLevel = new Level(preview, snake, *this->loadedLevelSpawner, frameDurationMs);
}

Level::Preview LevelSelector::GetLevel4Preview() const
{
	std::string name = "Level 4";
	constexpr int width = 8;
	constexpr int height = 8;
	Level::Element elements[] =
	{
		Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Empty, Level::Element::Empty, Level::Element::Block,
		Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block, Level::Element::Block, Level::Element::Empty, Level::Element::Block, Level::Element::Block,
	};
	constexpr Color backgroundColor = Colors::Red;

	return Level::Preview(name, width, height, elements, backgroundColor);
}

void LevelSelector::SelectNextOption()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (static_cast<int>(LevelSelector::Option::Last) < ++this->selectionCursor)
	{
		this->selectionCursor = static_cast<int>(LevelSelector::Option::First);
	}
}

void LevelSelector::SelectPreviousOption()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (static_cast<int>(LevelSelector::Option::First) > --this->selectionCursor)
	{
		this->selectionCursor = static_cast<int>(LevelSelector::Option::Last);
	}
}

void LevelSelector::SelectNextLevel()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (LevelSelector::numberOfLevels <= ++this->selectionValues[static_cast<int>(LevelSelector::Option::Level)])
	{
		this->selectionValues[static_cast<int>(LevelSelector::Option::Level)] = 0;
	}
	this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)] = static_cast<int>(Level::Difficulty::Lowest);
}

void LevelSelector::SelectPreviousLevel()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (0 > --this->selectionValues[static_cast<int>(LevelSelector::Option::Level)])
	{
		this->selectionValues[static_cast<int>(LevelSelector::Option::Level)] = LevelSelector::numberOfLevels - 1;
	}
	this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)] = static_cast<int>(Level::Difficulty::Lowest);
}

void LevelSelector::SelectNextDifficulty()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (static_cast<int>(Level::Difficulty::Highest) < ++this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)])
	{
		this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)] = static_cast<int>(Level::Difficulty::Lowest);
	}
}

void LevelSelector::SelectPreviousDifficulty()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (static_cast<int>(Level::Difficulty::Lowest) > --this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)])
	{
		this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)] = static_cast<int>(Level::Difficulty::Highest);
	}
}

LevelSelector::LevelSelector(Color backgroundColor, Color textColor, Color cursorColor, int frameDurationMs)
	: selectionValues{0, static_cast<int>(Level::Difficulty::Easy)}, selectionCursor(static_cast<int>(LevelSelector::Option::First)),
	  lastSelectionCursor(static_cast<int>(LevelSelector::Option::First)),
	  backgroundColor(backgroundColor), textColor(textColor), cursorColor(cursorColor),
	  loadedLevelSpawner(nullptr), loadedLevel(nullptr), frameDurationMs(frameDurationMs)
{ }

LevelSelector::~LevelSelector()
{
	delete this->loadedLevelSpawner;
	delete this->loadedLevel;
}

LevelSelector::Option LevelSelector::GetSelectionCursor() const
{
	return static_cast<LevelSelector::Option>(this->selectionCursor);
}

LevelSelector::Option LevelSelector::GetLastSelectionCursor() const
{
	return static_cast<LevelSelector::Option>(this->lastSelectionCursor);
}

LevelSelector::Option LevelSelector::GetCursorUpdate() const
{
	Option currentCursor = this->GetSelectionCursor();
	return currentCursor != this->GetLastSelectionCursor() ? Option::Count : currentCursor;
}

Level::Preview LevelSelector::GetSelectedLevelPreview() const
{
	return (this->*getLevelPreview[this->selectionValues[static_cast<int>(LevelSelector::Option::Level)]])();
}

Level::Difficulty LevelSelector::GetSelectedLevelDifficulty() const
{
	return static_cast<Level::Difficulty>(this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)]);
}

Color LevelSelector::GetBackgroundColor() const
{
	return this->backgroundColor;
}

Color LevelSelector::GetTextColor() const
{
	return this->textColor;
}

Color LevelSelector::GetCursorColor() const
{
	return this->cursorColor;
}

Level * LevelSelector::GetLoadedLevel() const
{
	return this->loadedLevel;
}

int LevelSelector::GetFrameDurationMs() const
{
	return this->frameDurationMs;
}

void LevelSelector::LoadSelectedLevel()
{
	delete this->loadedLevelSpawner;
	delete this->loadedLevel;

	this->loadedLevelSpawner = nullptr;
	this->loadedLevel = nullptr;

	(this->*loadLevel[this->selectionValues[static_cast<int>(LevelSelector::Option::Level)]])(static_cast<Level::Difficulty>(this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)]));
}

bool LevelSelector::Update(GameInput input)
{
	if (!input.IsValid())
	{
		return false;
	}

	switch (input.GetDirection())
	{
		case Direction::Up:
		{
			this->SelectPreviousOption();
		} break;
		case Direction::Down:
		{
			this->SelectNextOption();
		} break;
		case Direction::Right:
		{
			(this->*navigate[this->selectionCursor].second)();
		} break;
		case Direction::Left:
		{
			(this->*navigate[this->selectionCursor].first)();
		} break;
		default:
		  return false;
	}

	return true;
}

void LevelSelector::Reset()
{
	this->selectionValues[static_cast<int>(LevelSelector::Option::Level)] = 0;
	this->selectionValues[static_cast<int>(LevelSelector::Option::Difficulty)] = static_cast<int>(Level::Difficulty::Easy);

	this->selectionCursor = static_cast<int>(LevelSelector::Option::First);
	this->lastSelectionCursor = this->selectionCursor;
}
