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
#include "GameEngine.hpp"

#include "Helpers.hpp"

GameEngine::GameEngine(GameInputInterface& levelInputInterface, GameInputInterface& menuInputInterface, GameRenderer& gameRenderer, int windowFrameDurationMs)
	: levelInputInterface(&levelInputInterface), menuInputInterface(&menuInputInterface), gameRenderer(&gameRenderer),
	  levelSelector(Colors::Black, Colors::White, Colors::Green, windowFrameDurationMs),
	  currentState(&SelectLevelState::GetInstance())
{
	GameWindowButton pauseButtons[] =
	{
		GameWindowButton("Resume", [&](){this->currentState->SetState(*this, PlayLevelState::GetInstance());}),
		GameWindowButton("Back to menu", [&](){this->currentState->SetState(*this, SelectLevelState::GetInstance());})
	};
	GameWindowButton gameOverButtons[] =
	{
		GameWindowButton("Back to menu", [&](){this->currentState->SetState(*this, SelectLevelState::GetInstance());})
	};

	this->pauseWindow = new GameWindow("Game paused", pauseButtons, sizeof(pauseButtons) / sizeof(GameWindowButton),
		Colors::Black, Colors::White, Colors::Green, windowFrameDurationMs);
	this->gameOverWindow = new GameWindow("Game over", gameOverButtons, sizeof(gameOverButtons) / sizeof(GameWindowButton),
		Colors::Black, Colors::White, Colors::Green, windowFrameDurationMs);

	this->gameRenderer->SetCurrentLevelSelector(this->levelSelector);
}

GameEngine::~GameEngine()
{
	delete this->pauseWindow;
	delete this->gameOverWindow;
}

void GameEngine::Start()
{
	while (true)
	{
		bool isButtonPressed = this->currentState->GetGameInputInterface(*this)->IsButtonPressed();
		this->currentState->GetGameInputInterface(*this)->ResetButton();

		if (isButtonPressed)
		{
			this->currentState->OnSelect(*this);
			continue;
		}
		this->currentState->Update(*this);
	}
}
