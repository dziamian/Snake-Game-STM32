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
#include "GameState.hpp"

#include "stm32f1xx_hal.h"

GameState::~GameState()
{ }

void GameState::SetState(GameEngine& gameEngine, GameState& state) const
{
	gameEngine.currentState->OnExit(gameEngine);
	gameEngine.currentState = &state;
	gameEngine.currentState->OnEnter(gameEngine);
}

GameInputInterface * GameState::GetLevelInputInterface(GameEngine& gameEngine) const
{
	return gameEngine.levelInputInterface;
}

GameInputInterface * GameState::GetMenuInputInterface(GameEngine& gameEngine) const
{
	return gameEngine.menuInputInterface;
}

GameRenderer * GameState::GetGameRenderer(GameEngine& gameEngine) const
{
	return gameEngine.gameRenderer;
}

LevelSelector * GameState::GetLevelSelector(GameEngine& gameEngine) const
{
	return &gameEngine.levelSelector;
}

GameWindow * GameState::GetPauseWindow(GameEngine& gameEngine) const
{
	return gameEngine.pauseWindow;
}

GameWindow * GameState::GetGameOverWindow(GameEngine& gameEngine) const
{
	return gameEngine.gameOverWindow;
}

SelectLevelState::SelectLevelState()
{ }

void SelectLevelState::OnEnter(GameEngine& gameEngine)
{
	// Reset level selector.
	this->GetLevelSelector(gameEngine)->Reset();

	// Initialize level selection menu renderer.
	this->GetGameRenderer(gameEngine)->SetCurrentLevelSelector(*this->GetLevelSelector(gameEngine));
}

void SelectLevelState::OnExit(GameEngine& gameEngine)
{
	// Do nothing.
}

void SelectLevelState::Update(GameEngine& gameEngine)
{
	// Take game input.
	GameInput input = this->GetGameInputInterface(gameEngine)->GetGameInput();

	// Update level selector menu (logic).
	if (this->GetLevelSelector(gameEngine)->Update(input))
	{
		// Update level selector menu (graphics).
		this->GetGameRenderer(gameEngine)->DrawLevelSelection(this->GetLevelSelector(gameEngine)->GetCursorUpdate());
	}

	// Delay the next level selector menu frame.
	HAL_Delay(this->GetLevelSelector(gameEngine)->GetFrameDurationMs());
}

void SelectLevelState::OnSelect(GameEngine& gameEngine)
{
	// Load level chosen by the user.
	this->GetLevelSelector(gameEngine)->LoadSelectedLevel();

	// Start playing selected level.
	this->SetState(gameEngine, PlayLevelState::GetInstance());
}

GameState& SelectLevelState::GetInstance()
{
	static SelectLevelState singleton;
	return singleton;
}

GameInputInterface * SelectLevelState::GetGameInputInterface(GameEngine& gameEngine) const
{
	return this->GetMenuInputInterface(gameEngine);
}

PlayLevelState::PlayLevelState()
{ }

void PlayLevelState::OnEnter(GameEngine& gameEngine)
{
	// Initialize level renderer.
	this->GetGameRenderer(gameEngine)->SetCurrentLevel();
}

void PlayLevelState::OnExit(GameEngine& gameEngine)
{
	// Do nothing.
}

void PlayLevelState::Update(GameEngine& gameEngine)
{
	// Take game input.
	GameInput input = this->GetGameInputInterface(gameEngine)->GetGameInput();

	// Update game loop (logic).
	if (!this->GetLevelSelector(gameEngine)->GetLoadedLevel()->Update(input))
	{
		// If it fails then it's game over.
		this->SetState(gameEngine, GameOverState::GetInstance());
		return;
	}
	// Update game loop (graphics).
	this->GetGameRenderer(gameEngine)->DrawLevel();

	// Delay the next game frame.
	HAL_Delay(this->GetLevelSelector(gameEngine)->GetLoadedLevel()->GetFrameDurationMs());
}

void PlayLevelState::OnSelect(GameEngine& gameEngine)
{
	// Pause the game.
	this->SetState(gameEngine, PauseLevelState::GetInstance());
}

GameState& PlayLevelState::GetInstance()
{
	static PlayLevelState singleton;
	return singleton;
}

GameInputInterface * PlayLevelState::GetGameInputInterface(GameEngine& gameEngine) const
{
	return this->GetLevelInputInterface(gameEngine);
}

PauseLevelState::PauseLevelState()
{ }

void PauseLevelState::OnEnter(GameEngine& gameEngine)
{
	// Reset pause window.
	this->GetPauseWindow(gameEngine)->Reset();

	// Initialize pause selection menu renderer.
	this->GetGameRenderer(gameEngine)->SetCurrentWindow(*this->GetPauseWindow(gameEngine));
}

void PauseLevelState::OnExit(GameEngine& gameEngine)
{
	// Do nothing.
}

void PauseLevelState::Update(GameEngine& gameEngine)
{
	// Take game input.
	GameInput input = this->GetGameInputInterface(gameEngine)->GetGameInput();

	// Update pause selection menu (logic).
	this->GetPauseWindow(gameEngine)->Update(input);

	// Update pause selection menu (graphics).
	this->GetGameRenderer(gameEngine)->DrawGameWindow(false);

	// Delay the next pause selection menu frame.
	HAL_Delay(this->GetPauseWindow(gameEngine)->GetFrameDurationMs());
}

void PauseLevelState::OnSelect(GameEngine& gameEngine)
{
	this->GetPauseWindow(gameEngine)->SelectCurrentButton();
}

GameState& PauseLevelState::GetInstance()
{
	static PauseLevelState singleton;
	return singleton;
}

GameInputInterface * PauseLevelState::GetGameInputInterface(GameEngine& gameEngine) const
{
	return this->GetMenuInputInterface(gameEngine);
}

GameOverState::GameOverState()
{ }

void GameOverState::OnEnter(GameEngine& gameEngine)
{
	// Reset game over window.
	this->GetGameOverWindow(gameEngine)->Reset();

	// Initialize game over screen renderer.
	this->GetGameRenderer(gameEngine)->SetCurrentWindow(*this->GetGameOverWindow(gameEngine));
}

void GameOverState::OnExit(GameEngine& gameEngine)
{
	// Do nothing.
}

void GameOverState::Update(GameEngine& gameEngine)
{
	// Take game input.
	GameInput input = this->GetGameInputInterface(gameEngine)->GetGameInput();

	// Update game over screen (logic).
	this->GetGameOverWindow(gameEngine)->Update(input);

	// Update game over screen (graphics).
	this->GetGameRenderer(gameEngine)->DrawGameWindow(false);

	// Delay the next game over screen frame.
	HAL_Delay(this->GetGameOverWindow(gameEngine)->GetFrameDurationMs());
}

void GameOverState::OnSelect(GameEngine& gameEngine)
{
	this->GetGameOverWindow(gameEngine)->SelectCurrentButton();
}

GameState& GameOverState::GetInstance()
{
	static GameOverState singleton;
	return singleton;
}

GameInputInterface * GameOverState::GetGameInputInterface(GameEngine& gameEngine) const
{
	return this->GetMenuInputInterface(gameEngine);
}

