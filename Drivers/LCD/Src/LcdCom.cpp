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
#include "LcdCom.hpp"

LcdSpi::LcdSpi(SPI_HandleTypeDef * spi, GPIO_TypeDef * dcGpioPort, const uint16_t dcPin,
		GPIO_TypeDef * csGpioPort, const uint16_t csPin,
		GPIO_TypeDef * resetGpioPort, const uint16_t resetPin)
	: spi(spi), dcGpioPort(dcGpioPort), dcPin(dcPin),
	  csGpioPort(csGpioPort), csPin(csPin),
	  resetGpioPort(resetGpioPort), resetPin(resetPin)
{ }

GPIO_TypeDef * LcdSpi::GetResetGpioPort() const
{
	return this->resetGpioPort;
}

uint16_t LcdSpi::GetResetPin() const
{
	return this->resetPin;
}

bool LcdSpi::WriteCmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(dcGpioPort, dcPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_SET);

	return true;
}

bool LcdSpi::WriteSingleBytes(uint8_t * data, size_t dataSize)
{
	HAL_GPIO_WritePin(dcGpioPort, dcPin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, data, dataSize, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_SET);

	return true;
}

bool LcdSpi::WriteTwoBytes(uint16_t data)
{
	uint8_t data8[2] =
	{
		static_cast<uint8_t>((data >> 8) & 255),
		static_cast<uint8_t>(data & 255)
	};

	HAL_GPIO_WritePin(dcGpioPort, dcPin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, data8, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(csGpioPort, csPin, GPIO_PIN_SET);

	return true;
}
