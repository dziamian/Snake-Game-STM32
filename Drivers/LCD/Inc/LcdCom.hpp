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
#ifndef LCD_INC_LCDCOM_HPP_
#define LCD_INC_LCDCOM_HPP_

#include <stdint.h>

#include "stm32f1xx_hal.h"

class LcdCom
{
public:
	virtual bool WriteCmd(uint8_t cmd) = 0;
	virtual bool WriteSingleBytes(uint8_t * data, size_t dataSize) = 0;
	virtual bool WriteTwoBytes(uint16_t data) = 0;
};

class LcdSpi : public LcdCom
{
private:
	SPI_HandleTypeDef * spi;
	GPIO_TypeDef * dcGpioPort;
	const uint16_t dcPin;
	GPIO_TypeDef * csGpioPort;
	const uint16_t csPin;
	GPIO_TypeDef * resetGpioPort;
	const uint16_t resetPin;

public:
	LcdSpi(SPI_HandleTypeDef * spi, GPIO_TypeDef * dcGpioPort, const uint16_t dcPin,
			GPIO_TypeDef * csGpioPort, const uint16_t csPin,
			GPIO_TypeDef * resetGpioPort, const uint16_t resetPin);
	GPIO_TypeDef * GetResetGpioPort() const;
	uint16_t GetResetPin() const;

	bool WriteCmd(uint8_t cmd);
	bool WriteSingleBytes(uint8_t * data, size_t dataSize);
	bool WriteTwoBytes(uint16_t data);
};

#endif /* LCD_INC_LCDCOM_HPP_ */
