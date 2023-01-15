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
#ifndef INC_GAMESTATE_HPP_
#define INC_GAMESTATE_HPP_

#include "GameEngine.hpp"

class GameEngine;
class GameState
{
	friend class GameEngine;

	virtual void OnEnter(GameEngine& gameEngine) = 0;
	virtual void OnExit(GameEngine& gameEngine) = 0;

public:
	virtual void Update(GameEngine& gameEngine) = 0;
	virtual void OnSelect(GameEngine& gameEngine) = 0;
	virtual ~GameState();

protected:
	virtual GameInputInterface * GetGameInputInterface(GameEngine& gameEngine) const = 0;
	void SetState(GameEngine& gameEngine, GameState& state) const;

	GameInputInterface * GetLevelInputInterface(GameEngine& gameEngine) const;
	GameInputInterface * GetMenuInputInterface(GameEngine& gameEngine) const;
	GameRenderer * GetGameRenderer(GameEngine& gameEngine) const;
	LevelSelector * GetLevelSelector(GameEngine& gameEngine) const;
	GameWindow * GetPauseWindow(GameEngine& gameEngine) const;
	GameWindow * GetGameOverWindow(GameEngine& gameEngine) const;
};

class SelectLevelState : public GameState
{
	SelectLevelState();
	void OnEnter(GameEngine& gameEngine);
	void OnExit(GameEngine& gameEngine);

public:
	void Update(GameEngine& gameEngine);
	void OnSelect(GameEngine& gameEngine);

	static GameState& GetInstance();

protected:
	GameInputInterface * GetGameInputInterface(GameEngine& gameEngine) const;
};

class PlayLevelState : public GameState
{
	PlayLevelState();
	void OnEnter(GameEngine& gameEngine);
	void OnExit(GameEngine& gameEngine);

public:
	void Update(GameEngine& gameEngine);
	void OnSelect(GameEngine& gameEngine);

	static GameState& GetInstance();

protected:
	GameInputInterface * GetGameInputInterface(GameEngine& gameEngine) const;
};

class PauseLevelState : public GameState
{
	PauseLevelState();
	void OnEnter(GameEngine& gameEngine);
	void OnExit(GameEngine& gameEngine);

public:
	void Update(GameEngine& gameEngine);
	void OnSelect(GameEngine& gameEngine);

	static GameState& GetInstance();

protected:
	GameInputInterface * GetGameInputInterface(GameEngine& gameEngine) const;
};

class GameOverState : public GameState
{
	GameOverState();
	void OnEnter(GameEngine& gameEngine);
	void OnExit(GameEngine& gameEngine);

public:
	void Update(GameEngine& gameEngine);
	void OnSelect(GameEngine& gameEngine);

	static GameState& GetInstance();

protected:
	GameInputInterface * GetGameInputInterface(GameEngine& gameEngine) const;
};

#endif /* INC_GAMESTATE_HPP_ */
