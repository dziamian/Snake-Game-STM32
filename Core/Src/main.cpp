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
#include "GameConfig.hpp"

#include "GameEngine.hpp"
#include "GameRendererLcd.hpp"
#include "GameInputJoystick.hpp"
#include "JoystickAdc.hpp"
#include "LcdSsd1283a.hpp"

#include "LcdBasicFont.hpp"
#include "LcdImageBlock.hpp"
#include "LcdImageEmpty.hpp"
#include "LcdImageFruit.hpp"
#include "LcdImageFruitInTail.hpp"
#include "LcdImageSnakeFragment.hpp"
#include "LcdImageSnakeHead.hpp"
#include "LcdImageSnakeFruitHead.hpp"

/**
 * @brief  The application entry point.
 * @retval int
 */
int main()
{
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_SPI1_Init();

	HAL_TIM_Base_Start(&htim1);

	JoystickAdc joystick = JoystickAdc(&hadc1, 2000, 0.5f, BTN_Pin, 50);
	gJoystick = &joystick;

	LcdSpi lcdCom = LcdSpi(&hspi1, LCD_DC_GPIO_Port, LCD_DC_Pin, LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_RST_GPIO_Port, LCD_RST_Pin);
	LcdSsd1283a lcd = LcdSsd1283a(lcdCom);
	const LcdImage * levelElementImages[] =
	{
		&lcdImageEmpty,
		&lcdImageBlock,
		&lcdImageSnakeFragment,
		&lcdImageFruit,
		&lcdImageFruitInTail,
		&lcdImageSnakeHead,
		&lcdImageSnakeFruitHead
	};
	GameInputJoystick gameJoystick = GameInputJoystick(joystick, true, false, false);
	GameInputJoystick menuJoystick = GameInputJoystick(joystick, true, true, true);
	GameRendererLcd gameRenderer = GameRendererLcd(GameRenderer::LevelDrawMode::Full, lcd, lcdBasicFont, -2, 2, levelElementImages);
	constexpr int windowFrameDurationMs = 333;
	GameEngine gameEngine = GameEngine(gameJoystick, menuJoystick, gameRenderer, windowFrameDurationMs);
	gameEngine.Start();
}
