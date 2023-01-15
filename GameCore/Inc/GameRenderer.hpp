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
#ifndef INC_GAMERENDERER_HPP_
#define INC_GAMERENDERER_HPP_

#include "LevelSelector.hpp"
#include "GameWindow.hpp"
#include "Helpers.hpp"

class GameRenderer
{
public:
	enum class LevelDrawMode
	{
		UpdatesOnly,
		Full,
		Count
	};
	enum GameRendererOffset
	{
		Level,
		LevelName,
		LevelDifficulty,
		LevelSelectionCursorSpacing,
		WindowTitle,
		WindowButton,
		WindowButtonSpacing,
		WindowCursorSpacing,
		Count
	};

private:
	LevelSelector * levelSelector;
	LevelDrawMode levelDrawMode;
	GameWindow * gameWindow;

	bool (GameRenderer::* const levelDrawFunctions[static_cast<int>(LevelDrawMode::Count)])(::Level&) =
	{
		&GameRenderer::DrawLevelUpdates,
		&GameRenderer::DrawFullLevel
	};

	bool UpdateLevelSurroundings(::Level& level);
	bool UpdateLevelSnake(::Level& level);

	bool DrawLevelUpdates(::Level& level);
	bool DrawFullLevel(::Level& level);
	bool DrawFullLevel(::Level::Preview preview);

protected:
	Point2D offset[GameRendererOffset::Count];

	GameRenderer(LevelDrawMode levelDrawMode);

	virtual bool DrawBackground(Color backgroundColor) = 0;
	virtual bool DrawLevelName(LevelSelector& levelSelector) = 0;
	virtual bool DrawLevelDifficulty(LevelSelector& levelSelector) = 0;
	virtual bool DrawLevelSelectionCursor(LevelSelector& levelSelector) = 0;

	virtual bool DrawWindowTitle(GameWindow& gameWindow) = 0;
	virtual bool DrawWindowButton(GameWindow& gameWindow, int buttonIndex) = 0;
	virtual bool DrawWindowCursor(GameWindow& gameWindow) = 0;

	virtual bool DrawLevelElement(const Level::Element levelElement, const Point2D position) = 0;

	virtual bool InitializeLevelSelection(LevelSelector& levelSelector) = 0;
	virtual bool InitializeLevel(const ::Level::Preview& preview) = 0;
	virtual bool InitializeGameWindow(GameWindow& gameWindow) = 0;

public:
	void SetLevelDrawMode(LevelDrawMode levelDrawMode);

	void SetOffset(Point2D offset, GameRendererOffset offsetSelection);

	bool SetCurrentLevelSelector(LevelSelector& levelSelector);
	bool SetCurrentLevel();
	bool SetCurrentWindow(GameWindow& gameWindow);

	bool DrawLevelSelection(LevelSelector::Option option);
	bool DrawLevel();
	bool DrawGameWindow(bool fullDraw);
};

#endif /* INC_GAMERENDERER_HPP_ */
