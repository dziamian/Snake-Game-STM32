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
#ifndef INC_LEVELSELECTOR_HPP_
#define INC_LEVELSELECTOR_HPP_

#include "Level.hpp"
#include "LevelSpawner.hpp"

class LevelSelector
{
	friend class LevelSelectorRenderer;

public:
	enum class Option : int
	{
		Level,
		Difficulty,
		Count,
		First = Level,
		Last = Difficulty
	};

private:
	int selectionValues[static_cast<int>(LevelSelector::Option::Last) + 1];
	int selectionCursor;
	int lastSelectionCursor;

	Color backgroundColor;
	Color textColor;
	Color cursorColor;

	LevelSpawner * loadedLevelSpawner;
	Level * loadedLevel;

	int frameDurationMs;

	static constexpr int numberOfLevels = 4;

	void (LevelSelector::* const loadLevel[numberOfLevels])(Level::Difficulty) =
	{
		&LevelSelector::LoadLevel1,
		&LevelSelector::LoadLevel2,
		&LevelSelector::LoadLevel3,
		&LevelSelector::LoadLevel4
	};
	Level::Preview (LevelSelector::* const getLevelPreview[numberOfLevels])() const =
	{
		&LevelSelector::GetLevel1Preview,
		&LevelSelector::GetLevel2Preview,
		&LevelSelector::GetLevel3Preview,
		&LevelSelector::GetLevel4Preview
	};
	std::pair<void (LevelSelector::* const)(), void (LevelSelector::* const)()> navigate[static_cast<int>(LevelSelector::Option::Last) + 1] =
	{
		{ &LevelSelector::SelectPreviousLevel, &LevelSelector::SelectNextLevel },
		{ &LevelSelector::SelectPreviousDifficulty, &LevelSelector::SelectNextDifficulty }
	};

	void LoadLevel1(Level::Difficulty difficulty);
	Level::Preview GetLevel1Preview() const;

	void LoadLevel2(Level::Difficulty difficulty);
	Level::Preview GetLevel2Preview() const;

	void LoadLevel3(Level::Difficulty difficulty);
	Level::Preview GetLevel3Preview() const;

	void LoadLevel4(Level::Difficulty difficulty);
	Level::Preview GetLevel4Preview() const;

	void SelectNextOption();
	void SelectPreviousOption();

	void SelectNextLevel();
	void SelectPreviousLevel();

	void SelectNextDifficulty();
	void SelectPreviousDifficulty();

public:
	LevelSelector(Color backgroundColor, Color textColor, Color cursorColor, int frameDurationMs);
	~LevelSelector();
	Option GetSelectionCursor() const;
	Option GetLastSelectionCursor() const;
	Option GetCursorUpdate() const;
	Level::Preview GetSelectedLevelPreview() const;
	Level::Difficulty GetSelectedLevelDifficulty() const;
	Color GetBackgroundColor() const;
	Color GetTextColor() const;
	Color GetCursorColor() const;
	Level * GetLoadedLevel() const;
	int GetFrameDurationMs() const;
	void LoadSelectedLevel();
	bool Update(GameInput input);
	void Reset();
};

#endif /* INC_LEVELSELECTOR_HPP_ */
