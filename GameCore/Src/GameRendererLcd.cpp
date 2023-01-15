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
#include "GameRendererLcd.hpp"

GameRendererLcd::GameRendererLcd(LevelDrawMode levelDrawMode, Lcd& lcd, const LcdFont& font,
		const int16_t letterSpacing, const int16_t lineSpacing,
		const LcdImage * levelElementImages[static_cast<int>(Level::Element::Count)])
	: GameRenderer(levelDrawMode), lcd(&lcd), font(&font),
	  letterSpacing(letterSpacing), lineSpacing(lineSpacing),
	  levelElementImages(levelElementImages),
	  lastLevelNameSize(0), lastLevelDifficultySize(0)
{ }

bool GameRendererLcd::DrawBackground(Color backgroundColor)
{
	if (Lcd::Error::Ok != this->lcd->ClearScreen(backgroundColor.GetRgb565()))
	{
		return false;
	}

	return true;
}

bool GameRendererLcd::DrawLevelName(LevelSelector& levelSelector)
{
	constexpr int numberOfDraws = 2;
	std::string names[numberOfDraws] =
	{
		std::string(this->lastLevelNameSize, ' '),
		"<- " + levelSelector.GetSelectedLevelPreview().GetName() + " ->"
	};

	this->lastLevelNameSize = names[1].length();

	for (int i = 0; i < numberOfDraws; ++i)
	{
		if (Lcd::Error::Ok != this->lcd->DrawText(
			this->offset[GameRendererOffset::LevelName].GetX(),
			this->offset[GameRendererOffset::LevelName].GetY(),
			names[i],
			this->letterSpacing, this->lineSpacing,
			*this->font,
			levelSelector.GetTextColor().GetRgb565(),
			levelSelector.GetBackgroundColor().GetRgb565())
		)
		{
			return false;
		}
	}

	return true;
}

bool GameRendererLcd::DrawLevelDifficulty(LevelSelector& levelSelector)
{
	constexpr int numberOfDraws = 2;
	std::string names[numberOfDraws] =
	{
		std::string(this->lastLevelDifficultySize, ' '),
		"<- " + ::Level::difficultyNames[static_cast<int>(levelSelector.GetSelectedLevelDifficulty())] + " ->"
	};

	this->lastLevelDifficultySize = names[1].length();

	for (int i = 0; i < numberOfDraws; ++i)
	{
		if (Lcd::Error::Ok != this->lcd->DrawText(
			this->offset[GameRendererOffset::LevelDifficulty].GetX(),
			this->offset[GameRendererOffset::LevelDifficulty].GetY(),
			names[i],
			this->letterSpacing, this->lineSpacing,
			*this->font,
			levelSelector.GetTextColor().GetRgb565(),
			levelSelector.GetBackgroundColor().GetRgb565())
		)
		{
			return false;
		}
	}

	return true;
}

bool GameRendererLcd::DrawLevelSelectionCursor(LevelSelector& levelSelector)
{
	constexpr int numberOfDraws = 2;
	const int options[numberOfDraws] =
	{
		static_cast<int>(levelSelector.GetLastSelectionCursor()),
		static_cast<int>(levelSelector.GetSelectionCursor())
	};
	const Color colors[numberOfDraws] =
	{
		levelSelector.GetBackgroundColor(),
		levelSelector.GetCursorColor()
	};

	for (int i = 0; i < numberOfDraws; ++i)
	{
		if (Lcd::Error::Ok != this->lcd->DrawRectangle(
			this->offset[GameRendererOffset::LevelName + options[i]].GetX()
				+ this->offset[GameRendererOffset::LevelSelectionCursorSpacing].GetX(),
			this->offset[GameRendererOffset::LevelName + options[i]].GetY()
				+ this->offset[GameRendererOffset::LevelSelectionCursorSpacing].GetY(),
			this->font->width,
			this->font->height / 2,
			colors[i].GetRgb565())
		)
		{
			return false;
		}
	}

	return true;
}

bool GameRendererLcd::DrawWindowTitle(GameWindow& gameWindow)
{
	if (Lcd::Error::Ok != this->lcd->DrawText(
		this->offset[GameRendererOffset::WindowTitle].GetX(),
		this->offset[GameRendererOffset::WindowTitle].GetY(),
		gameWindow.GetTitle(),
		this->letterSpacing, this->lineSpacing,
		*this->font,
		gameWindow.GetTextColor().GetRgb565(),
		gameWindow.GetBackgroundColor().GetRgb565())
	)
	{
		return false;
	}

	return true;
}

bool GameRendererLcd::DrawWindowButton(GameWindow& gameWindow, int buttonIndex)
{
	if (Lcd::Error::Ok != this->lcd->DrawText(
		this->offset[GameRendererOffset::WindowButton].GetX()
			+ buttonIndex * this->offset[GameRendererOffset::WindowButtonSpacing].GetX(),
		this->offset[GameRendererOffset::WindowButton].GetY()
			+ buttonIndex * this->offset[GameRendererOffset::WindowButtonSpacing].GetY(),
		gameWindow.GetButton(buttonIndex)->GetName(),
		this->letterSpacing, this->lineSpacing,
		*this->font,
		gameWindow.GetTextColor().GetRgb565(),
		gameWindow.GetBackgroundColor().GetRgb565())
	)
	{
		return false;
	}

	return true;
}

bool GameRendererLcd::DrawWindowCursor(GameWindow& gameWindow)
{
	constexpr int numberOfDraws = 2;
	int options[numberOfDraws] =
	{
		gameWindow.GetLastButtonIndex(),
		gameWindow.GetCurrentButtonIndex()
	};
	Color colors[numberOfDraws] =
	{
		gameWindow.GetBackgroundColor(),
		gameWindow.GetCursorColor()
	};

	for (int i = 0; i < numberOfDraws; ++i)
	{
		if (Lcd::Error::Ok != this->lcd->DrawRectangle(
			this->offset[GameRendererOffset::WindowButton].GetX()
				+ options[i] * this->offset[GameRendererOffset::WindowButtonSpacing].GetX()
				+ this->offset[GameRendererOffset::WindowCursorSpacing].GetX(),
			this->offset[GameRendererOffset::WindowButton].GetY()
				+ options[i] * this->offset[GameRendererOffset::WindowButtonSpacing].GetY()
				+ this->offset[GameRendererOffset::WindowCursorSpacing].GetY(),
			this->font->width,
			this->font->height / 2,
			colors[i].GetRgb565())
		)
		{
			return false;
		}
	}

	return true;
}

bool GameRendererLcd::DrawLevelElement(const Level::Element levelElement, const Point2D position)
{
	const LcdImage& image = *this->levelElementImages[static_cast<int>(levelElement)];
	if (Lcd::Error::Ok != this->lcd->DrawImage(
		this->offset[GameRendererOffset::Level].GetX() + position.GetX() * image.width,
		this->offset[GameRendererOffset::Level].GetY() + position.GetY() * image.height,
		image))
	{
		return false;
	}
	return true;
}

bool GameRendererLcd::InitializeLevelSelection(LevelSelector& levelSelector)
{
	this->InitializeLevel(levelSelector.GetSelectedLevelPreview());

	this->SetOffset(Point2D(
		this->lcd->GetWidth() - this->font->width * 4.5,
		this->font->height / 2
	), GameRendererOffset::LevelName);
	this->SetOffset(Point2D(
		this->lcd->GetWidth() - this->font->width * 5,
		this->lcd->GetHeight() - this->font->height * 1.5
	), GameRendererOffset::LevelDifficulty);
	this->SetOffset(Point2D(
		this->font->width * 2,
		this->font->height / 4
	), GameRendererOffset::LevelSelectionCursorSpacing);

	return true;
}

bool GameRendererLcd::InitializeLevel(const ::Level::Preview& preview)
{
	const LcdImage& image = *this->levelElementImages[static_cast<int>(Level::Element::Block)];
	this->SetOffset(Point2D(
		this->lcd->GetWidth() / 2 - preview.GetWidth() * image.width / 2,
		this->lcd->GetHeight() / 2 - preview.GetHeight() * image.height / 2
	), GameRendererOffset::Level);

	return true;
}

bool GameRendererLcd::InitializeGameWindow(GameWindow& gameWindow)
{
	this->SetOffset(Point2D(
		this->lcd->GetWidth() - this->font->width * 6,
		this->font->height
	), GameRendererOffset::WindowTitle);
	this->SetOffset(Point2D(
		this->lcd->GetWidth() - this->font->width * 4,
		this->font->height * 4
	), GameRendererOffset::WindowButton);
	this->SetOffset(Point2D(
		0,
		this->font->height * 1.5
	), GameRendererOffset::WindowButtonSpacing);
	this->SetOffset(Point2D(
		this->font->width * 2,
		this->font->height / 4
	), GameRendererOffset::WindowCursorSpacing);

	return true;
}
