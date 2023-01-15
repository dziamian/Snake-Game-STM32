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
#ifndef INC_GAMEWINDOW_HPP_
#define INC_GAMEWINDOW_HPP_

#include <functional>
#include <string>

#include "Helpers.hpp"
#include "GameInput.hpp"

class GameWindowButton
{
	std::string name;
	std::function<void()> onSelect;

public:
	GameWindowButton();
	GameWindowButton(std::string name, std::function<void()> onSelect);
	GameWindowButton(const GameWindowButton& gameWindowButton) = default;
	std::string GetName() const;
	void OnSelect();
};

class GameWindow
{
	std::string title;
	GameWindowButton * buttons;
	int numberOfButtons;

	int selectionCursor;
	int lastSelectionCursor;

	Color backgroundColor;
	Color textColor;
	Color cursorColor;

	int frameDurationMs;

	void SelectNextButton();
	void SelectPreviousButton();

public:
	GameWindow(std::string title, GameWindowButton * buttons, int numberOfButtons,
		Color backgroundColor, Color textColor, Color cursorColor, int frameDurationMs);
	GameWindow(const GameWindow& gameWindow);
	GameWindow& operator = (const GameWindow& gameWindow) = delete;
	~GameWindow();
	std::string GetTitle() const;
	GameWindowButton * GetButton(int buttonIndex) const;
	int GetNumberOfButtons() const;
	int GetCurrentButtonIndex() const;
	int GetLastButtonIndex() const;
	Color GetBackgroundColor() const;
	Color GetTextColor() const;
	Color GetCursorColor() const;
	int GetFrameDurationMs() const;
	void SelectCurrentButton();
	void Update(GameInput input);
	void Reset();
};

#endif /* INC_GAMEWINDOW_HPP_ */
