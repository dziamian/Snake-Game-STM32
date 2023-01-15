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
#include "JoystickAdc.hpp"

#include <cmath>

JoystickAdc::JoystickAdc(ADC_HandleTypeDef * adcHandle, const uint16_t middleValue, const float deadzoneRatio,
		const uint16_t buttonPin, const uint32_t debounceTimeMs)
	: middleValue(middleValue), deadzoneValue(deadzoneRatio * middleValue),
	  buttonPin(buttonPin), debounceTimeMs(debounceTimeMs), previousDebounceTimeMs(0)
{
	HAL_ADC_Start_DMA(adcHandle, reinterpret_cast<uint32_t *>(this->values), 2);
}

JoystickInput JoystickAdc::GetInput()
{
	this->currentDirections[0] = (0 > this->values[0] - middleValue) ? Direction::Right : Direction::Left;
	this->currentDirections[1] = (0 > this->values[1] - middleValue) ? Direction::Up : Direction::Down;

	this->currentRelativeValues[0] = std::abs(this->values[0] - middleValue);
	this->currentRelativeValues[1] = std::abs(this->values[1] - middleValue);

	int index = (this->currentRelativeValues[0] > this->currentRelativeValues[1]) ? 0 : 1;

	return JoystickInput(
		this->currentDirections[index],
		this->currentRelativeValues[index] > this->deadzoneValue
	);
}

void JoystickAdc::ButtonExternalCallback(const uint16_t pin)
{
	if (this->buttonPin != pin)
	{
		return;
	}

	uint32_t currentDebounceTimeMs = HAL_GetTick();
	if ((currentDebounceTimeMs - this->previousDebounceTimeMs) > this->debounceTimeMs)
	{
		this->isButtonPressed = true;
		this->previousDebounceTimeMs = currentDebounceTimeMs;
	}
	else
	{
		__NOP();
	}
}
