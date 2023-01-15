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
#include <GameWindow.hpp>

GameWindowButton::GameWindowButton()
{ }

GameWindowButton::GameWindowButton(std::string name, std::function<void()> onSelect)
	: name(name), onSelect(onSelect)
{ }

std::string GameWindowButton::GetName() const
{
	return this->name;
}

void GameWindowButton::OnSelect()
{
	this->onSelect();
}

void GameWindow::SelectNextButton()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (this->numberOfButtons <= ++this->selectionCursor)
	{
		this->selectionCursor = 0;
	}
}

void GameWindow::SelectPreviousButton()
{
	this->lastSelectionCursor = this->selectionCursor;

	if (0 > --this->selectionCursor)
	{
		this->selectionCursor = this->numberOfButtons - 1;
	}
}

GameWindow::GameWindow(std::string title, GameWindowButton * buttons, int numberOfButtons,
		Color backgroundColor, Color textColor, Color cursorColor, int frameDurationMs)
	: title(title), numberOfButtons(numberOfButtons), selectionCursor(0), lastSelectionCursor(0),
	  backgroundColor(backgroundColor), textColor(textColor), cursorColor(cursorColor),
	  frameDurationMs(frameDurationMs)
{
	this->buttons = new GameWindowButton[numberOfButtons];
	for (int i = 0; i < numberOfButtons; ++i)
	{
		this->buttons[i] = GameWindowButton(buttons[i]);
	}
}

GameWindow::GameWindow(const GameWindow& gameWindow)
	: title(gameWindow.title), numberOfButtons(gameWindow.numberOfButtons),
	  selectionCursor(gameWindow.selectionCursor), lastSelectionCursor(gameWindow.lastSelectionCursor),
	  backgroundColor(gameWindow.backgroundColor), textColor(gameWindow.textColor), cursorColor(gameWindow.cursorColor),
	  frameDurationMs(gameWindow.frameDurationMs)
{
	this->buttons = new GameWindowButton[gameWindow.numberOfButtons];
	for (int i = 0; i < gameWindow.numberOfButtons; ++i)
	{
		this->buttons[i] = GameWindowButton(gameWindow.buttons[i]);
	}
}

GameWindow::~GameWindow()
{
	delete [] this->buttons;
}

std::string GameWindow::GetTitle() const
{
	return this->title;
}

GameWindowButton * GameWindow::GetButton(int buttonIndex) const
{
	return &this->buttons[buttonIndex];
}

int GameWindow::GetNumberOfButtons() const
{
	return this->numberOfButtons;
}

int GameWindow::GetCurrentButtonIndex() const
{
	return this->selectionCursor;
}

int GameWindow::GetLastButtonIndex() const
{
	return this->lastSelectionCursor;
}

Color GameWindow::GetBackgroundColor() const
{
	return this->backgroundColor;
}

Color GameWindow::GetTextColor() const
{
	return this->textColor;
}

Color GameWindow::GetCursorColor() const
{
	return this->cursorColor;
}

int GameWindow::GetFrameDurationMs() const
{
	return this->frameDurationMs;
}

void GameWindow::SelectCurrentButton()
{
	this->buttons[this->selectionCursor].OnSelect();
}

void GameWindow::Update(GameInput input)
{
	if (!input.IsValid())
	{
		return;
	}

	switch (input.GetDirection())
	{
		case Direction::Up:
		case Direction::Right:
		{
			this->SelectNextButton();
		} break;
		case Direction::Down:
		case Direction::Left:
		{
			this->SelectPreviousButton();
		} break;
		default:
		  break;
	}
}

void GameWindow::Reset()
{
	this->selectionCursor = 0;
}
