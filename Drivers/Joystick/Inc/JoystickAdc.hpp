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
#ifndef JOYSTICK_INC_JOYSTICKADC_HPP_
#define JOYSTICK_INC_JOYSTICKADC_HPP_

#include "Joystick.hpp"

#include "stm32f1xx_hal.h"

class JoystickAdc : public Joystick
{
	const uint16_t middleValue;
	const uint16_t deadzoneValue;
	uint16_t values[2];

	const uint16_t buttonPin;
	const uint32_t debounceTimeMs;
	volatile uint32_t previousDebounceTimeMs;

	Direction currentDirections[2];
	uint16_t currentRelativeValues[2];

public:
	JoystickAdc(ADC_HandleTypeDef * adcHandle, const uint16_t middleValue, const float deadzoneRatio,
			const uint16_t buttonPin, const uint32_t debounceTimeMs);
	JoystickInput GetInput();
	void ButtonExternalCallback(const uint16_t pin);
};


#endif /* JOYSTICK_INC_JOYSTICKADC_HPP_ */
