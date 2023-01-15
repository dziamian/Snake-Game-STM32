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
#include "GameRenderer.hpp"

bool GameRenderer::UpdateLevelSurroundings(::Level& level)
{
	for (Fruit const& i : level.spawnedFruits)
	{
		if (!this->DrawLevelElement(Level::Element::Fruit, i.position))
		{
			return false;
		}
	}

	return true;
}

bool GameRenderer::UpdateLevelSnake(::Level& level)
{
	Point2D positions[] =
	{
		level.snake.GetHead().position,
		level.snake.GetOldHead().position,
		level.snake.GetOldTail().position,
		level.snake.GetTail().position
	};
	for (Point2D position : positions)
	{
		if (!this->DrawLevelElement(level.preview.GetElement(position), position))
		{
			return false;
		}
	}

	return true;
}

bool GameRenderer::DrawLevelUpdates(::Level& level)
{
	if (!this->UpdateLevelSurroundings(level))
	{
		return false;
	}

	if (!this->UpdateLevelSnake(level))
	{
		return false;
	}

	return true;
}

bool GameRenderer::DrawFullLevel(::Level& level)
{
	return DrawFullLevel(level.preview);
}

bool GameRenderer::DrawFullLevel(::Level::Preview preview)
{
	for (int i = 0; i < preview.GetHeight(); ++i)
	{
		for (int j = 0; j < preview.GetWidth(); ++j)
		{
			Point2D position = Point2D(j, i);
			if (!this->DrawLevelElement(preview.GetElement(position), position))
			{
				return false;
			}
		}
	}

	return true;
}

GameRenderer::GameRenderer(LevelDrawMode levelDrawMode)
	: levelSelector(nullptr), levelDrawMode(levelDrawMode),
	  offset {
		Point2D(0, 0), Point2D(0, 0), Point2D(0, 0), Point2D(0, 0),
		Point2D(0, 0), Point2D(0, 0), Point2D(0, 0), Point2D(0, 0)
	  }
{ }

void GameRenderer::SetLevelDrawMode(LevelDrawMode levelDrawMode)
{
	this->levelDrawMode = levelDrawMode;
}

void GameRenderer::SetOffset(Point2D offset, GameRendererOffset offsetSelection)
{
	this->offset[offsetSelection] = offset;
}

bool GameRenderer::SetCurrentLevelSelector(LevelSelector& levelSelector)
{
	if (!this->InitializeLevelSelection(levelSelector))
	{
		return false;
	}

	this->levelSelector = &levelSelector;

	if (!this->DrawLevelSelection(LevelSelector::Option::Level))
	{
		return false;
	}

	return true;
}

bool GameRenderer::SetCurrentLevel()
{
	if (!this->DrawBackground(this->levelSelector->GetLoadedLevel()->GetPreview()->GetBackgroundColor()))
	{
		return false;
	}

	if (!this->InitializeLevel(*this->levelSelector->GetLoadedLevel()->GetPreview()))
	{
		return false;
	}

	if (!this->DrawFullLevel(*this->levelSelector->GetLoadedLevel()))
	{
		return false;
	}

	return true;
}

bool GameRenderer::SetCurrentWindow(GameWindow& gameWindow)
{
	if (!this->DrawBackground(gameWindow.GetBackgroundColor()))
	{
		return false;
	}

	if (!this->InitializeGameWindow(gameWindow))
	{
		return false;
	}

	this->gameWindow = &gameWindow;

	if (!this->DrawGameWindow(true))
	{
		return false;
	}

	return true;
}

bool GameRenderer::DrawLevelSelection(LevelSelector::Option option)
{
	if (nullptr == this->levelSelector)
	{
		return false;
	}

	if (LevelSelector::Option::Level == option)
	{
		::Level::Preview preview = this->levelSelector->GetSelectedLevelPreview();
		if (!this->DrawBackground(this->levelSelector->GetBackgroundColor()))
		{
			return false;
		}
		if (!this->InitializeLevel(preview))
		{
			return false;
		}

		if (!this->DrawFullLevel(preview))
		{
			return false;
		}

		if (!this->DrawLevelName(*this->levelSelector))
		{
			return false;
		}
	}

	if (LevelSelector::Option::Difficulty == option || LevelSelector::Option::Level == option)
	{
		if (!this->DrawLevelDifficulty(*this->levelSelector))
		{
			return false;
		}
	}

	if (LevelSelector::Option::Count == option || LevelSelector::Option::Level == option)
	{
		if (!this->DrawLevelSelectionCursor(*this->levelSelector))
		{
			return false;
		}
	}

	return true;
}

bool GameRenderer::DrawLevel()
{
	if (nullptr == this->levelSelector->GetLoadedLevel())
	{
		return false;
	}

	return (this->*levelDrawFunctions[static_cast<int>(this->levelDrawMode)])(*this->levelSelector->GetLoadedLevel());
}

bool GameRenderer::DrawGameWindow(bool fullDraw)
{
	if (nullptr == this->gameWindow)
	{
		return false;
	}

	if (fullDraw)
	{
		if (!this->DrawWindowTitle(*this->gameWindow))
		{
			return false;
		}

		int numberOfButtons = this->gameWindow->GetNumberOfButtons();
		for (int i = 0; i < numberOfButtons; ++i)
		{
			if (!this->DrawWindowButton(*this->gameWindow, i))
			{
				return false;
			}
		}
	}

	if (!this->DrawWindowCursor(*this->gameWindow))
	{
		return false;
	}

	return true;
}
