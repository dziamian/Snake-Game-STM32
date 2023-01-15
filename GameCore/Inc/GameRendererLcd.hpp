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
#ifndef INC_GAMERENDERERLCD_HPP_
#define INC_GAMERENDERERLCD_HPP_

#include "GameRenderer.hpp"
#include "Lcd.hpp"

class GameRendererLcd : public GameRenderer
{
	Lcd * lcd;
	const LcdFont * font;
	const int16_t letterSpacing;
	const int16_t lineSpacing;
	const LcdImage **levelElementImages;

	uint16_t lastLevelNameSize;
	uint16_t lastLevelDifficultySize;

public:
	GameRendererLcd(LevelDrawMode levelDrawMode, Lcd& lcd, const LcdFont& font,
			const int16_t letterSpacing, const int16_t lineSpacing,
			const LcdImage * levelElementImages[static_cast<int>(Level::Element::Count)]);

	bool DrawBackground(Color backgroundColor);
	bool DrawLevelName(LevelSelector& levelSelector);
	bool DrawLevelDifficulty(LevelSelector& levelSelector);
	bool DrawLevelSelectionCursor(LevelSelector& levelSelector);

	bool DrawWindowTitle(GameWindow& gameWindow);
	bool DrawWindowButton(GameWindow& gameWindow, int buttonIndex);
	bool DrawWindowCursor(GameWindow& gameWindow);

	bool DrawLevelElement(const Level::Element levelElement, const Point2D position);

	bool InitializeLevelSelection(LevelSelector& levelSelector);
	bool InitializeLevel(const ::Level::Preview& preview);
	bool InitializeGameWindow(GameWindow& gameWindow);
};

#endif /* INC_GAMERENDERERLCD_HPP_ */
