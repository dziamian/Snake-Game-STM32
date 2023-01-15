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
#include "LcdSsd1283a.hpp"

#include <stdexcept>

#include "helpers.h"

uint8_t LcdSsd1283a::displayOnCommands[][commandHandleSize] =
{
	{LcdSsd1283a::Registers::DISPLAY_CTRL, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON1_MSB, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON1_LSB},
	{LcdSsd1283a::Registers::OSCILLATION, LcdSsd1283a::RegisterValues::OSCILLATION_DISPLAYON_MSB, LcdSsd1283a::RegisterValues::OSCILLATION_DISPLAYON_LSB},
	{LcdSsd1283a::Registers::DISPLAY_CTRL, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON2_MSB, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON2_LSB},
	{LcdSsd1283a::Registers::POWER_CTRL_1, LcdSsd1283a::RegisterValues::POWER_CTRL_1_DISPLAYON_MSB, LcdSsd1283a::RegisterValues::POWER_CTRL_1_DISPLAYON_LSB},
	{LcdSsd1283a::Registers::DISPLAY_CTRL, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON3_MSB, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYON3_LSB},
};
uint8_t LcdSsd1283a::displayOffCommands[][commandHandleSize] =
{
	{LcdSsd1283a::Registers::DISPLAY_CTRL, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYOFF_MSB, LcdSsd1283a::RegisterValues::DISPLAY_CTRL_DISPLAYOFF_LSB},
	{LcdSsd1283a::Registers::OSCILLATION, LcdSsd1283a::RegisterValues::OSCILLATION_DISPLAYOFF_MSB, LcdSsd1283a::RegisterValues::OSCILLATION_DISPLAYOFF_LSB},
	{LcdSsd1283a::Registers::POWER_CTRL_1, LcdSsd1283a::RegisterValues::POWER_CTRL_1_DISPLAYOFF_MSB, LcdSsd1283a::RegisterValues::POWER_CTRL_1_DISPLAYOFF_LSB}
};
uint8_t LcdSsd1283a::initCommands[][commandHandleSize] =
{
	{LcdSsd1283a::Registers::DRIVER_OUTPUT_CTRL, LcdSsd1283a::RegisterValues::DRIVER_OUTPUT_CTRL_INIT_MSB, LcdSsd1283a::RegisterValues::DRIVER_OUTPUT_CTRL_INIT_LSB},
	{LcdSsd1283a::Registers::ENTRY_MODE, LcdSsd1283a::RegisterValues::ENTRY_MODE_INIT_MSB, LcdSsd1283a::RegisterValues::ENTRY_MODE_INIT_LSB},
	{LcdSsd1283a::Registers::DRIVER_AC_CTRL, LcdSsd1283a::RegisterValues::DRIVER_AC_CTRL_INIT_MSB, LcdSsd1283a::RegisterValues::DRIVER_AC_CTRL_INIT_LSB},
};

Lcd::Error LcdSsd1283a::SendSetOfCommands(uint8_t commands[][LcdSsd1283a::commandHandleSize], const size_t numberOfRows) const
{
	for (size_t i = 0; i < numberOfRows; ++i)
	{
		if (!this->com->WriteCmd(commands[i][0]))
		{
			return Lcd::Error::CommunicationFailed;
		}
		if (!this->com->WriteSingleBytes(&commands[i][1], 2))
		{
			return Lcd::Error::CommunicationFailed;
		}
	}

	return Lcd::Error::Ok;
}

Lcd::Error LcdSsd1283a::DrawChar(const uint8_t x, const uint8_t y, const char character,
			const LcdFont& font, const uint16_t fontColor, const uint16_t backgroundColor) const
{
	Lcd::Error status = this->InitWindow(x, y, font.width, font.height);
	if (Lcd::Error::Ok != status)
	{
		return status;
	}

	if (!this->com->WriteCmd(Registers::RAM_WRITE))
	{
		return Lcd::Error::CommunicationFailed;
	}
	for (int i = 0; i < font.height; ++i)
	{
		for (int j = 0; j < font.width; ++j)
		{
			bool pixel;
			if (!font.GetPixel(character, j, i, pixel))
			{
				return Lcd::Error::InvalidResource;
			}
			if (!this->com->WriteTwoBytes(pixel ? fontColor : backgroundColor))
			{
				return Lcd::Error::CommunicationFailed;
			}
		}
	}

	return Lcd::Error::Ok;
}

Lcd::Error LcdSsd1283a::InitWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height) const
{
	uint8_t data[dataSize];
	data[0] = x + width - 1;
	data[1] = x;
	if (!this->com->WriteCmd(Registers::HORIZONTAL_RAM_SET))
	{
		return Lcd::Error::CommunicationFailed;
	}
	if (!this->com->WriteSingleBytes(data, 2))
	{
		return Lcd::Error::CommunicationFailed;
	}

	data[0] = y + height - 1;
	data[1] = y;
	if (!this->com->WriteCmd(Registers::VERTICAL_RAM_SET))
	{
		return Lcd::Error::CommunicationFailed;
	}
	if (!this->com->WriteSingleBytes(data, 2))
	{
		return Lcd::Error::CommunicationFailed;
	}

	data[0] = y;
	data[1] = x + width - 1;
	if (!this->com->WriteCmd(Registers::RAM_SET))
	{
		return Lcd::Error::CommunicationFailed;
	}
	if (!this->com->WriteSingleBytes(data, 2))
	{
		return Lcd::Error::CommunicationFailed;
	}

	return Lcd::Error::Ok;
}

LcdSsd1283a::LcdSsd1283a(LcdSpi& spiCom)
	: Lcd(LcdSsd1283a::width, LcdSsd1283a::height, spiCom)
{
	// Reset display
	HAL_GPIO_WritePin(spiCom.GetResetGpioPort(), spiCom.GetResetPin(), GPIO_PIN_RESET);
	HAL_Delay_Us(LcdSsd1283a::resetUs);
	HAL_GPIO_WritePin(spiCom.GetResetGpioPort(), spiCom.GetResetPin(), GPIO_PIN_SET);
	HAL_Delay_Us(LcdSsd1283a::resetUs);

	Lcd::Error status = this->DisplayOn();
	if (Lcd::Error::Ok != status)
	{
		throw std::runtime_error("Couldn't turn on the display during initialization.");
	}

	status = this->SendSetOfCommands(initCommands, sizeof(initCommands) / sizeof(initCommands[0]));
	if (Lcd::Error::Ok != status)
	{
		throw std::runtime_error("Couldn't initialize the display.");
	}
}

LcdSsd1283a::~LcdSsd1283a()
{ }

Lcd::Error LcdSsd1283a::DisplayOn()
{
	return this->SendSetOfCommands(displayOnCommands, sizeof(displayOnCommands) / sizeof(displayOnCommands[0]));
}

Lcd::Error LcdSsd1283a::DisplayOff()
{
	return this->SendSetOfCommands(displayOffCommands, sizeof(displayOffCommands) / sizeof(displayOffCommands[0]));
}

Lcd::Error LcdSsd1283a::DrawRectangle(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, const uint16_t color)
{
	Lcd::Error status = this->InitWindow(x, y, width, height);
	if (Lcd::Error::Ok != status)
	{
		return status;
	}

	if (!this->com->WriteCmd(Registers::RAM_WRITE))
	{
		return Lcd::Error::CommunicationFailed;
	}
	uint16_t rectSize = width * height;
	for (int i = 0; i < rectSize; ++i)
	{
		if (!this->com->WriteTwoBytes(color))
		{
			return Lcd::Error::CommunicationFailed;
		}
	}

	return Lcd::Error::Ok;
}

Lcd::Error LcdSsd1283a::DrawImage(const uint16_t x, const uint16_t y, const LcdImage& image)
{
	Lcd::Error status = this->InitWindow(x, y, image.width, image.height);
	if (Lcd::Error::Ok != status)
	{
		return status;
	}

	if (!this->com->WriteCmd(Registers::RAM_WRITE))
	{
		return Lcd::Error::CommunicationFailed;
	}
	for (int i = 0; i < image.height; ++i)
	{
		for (int j = 0; j < image.width; ++j)
		{
			uint16_t pixel;
			if (!image.GetPixel(j, i, pixel))
			{
				return Lcd::Error::InvalidResource;
			}
			if (!this->com->WriteTwoBytes(pixel))
			{
				return Lcd::Error::CommunicationFailed;
			}
		}
	}

	return Lcd::Error::Ok;
}

Lcd::Error LcdSsd1283a::DrawText(uint16_t x, uint16_t y, std::string text,
	  const int16_t letterSpacing, const int16_t lineSpacing, const LcdFont& font,
	  const uint16_t fontColor, const uint16_t backgroundColor)
{
	Lcd::Error status;
	size_t textLength = text.length();
	uint16_t startX = x;
	for (size_t textIndex = 0; textIndex < textLength; ++textIndex)
	{
		if ('\n' == text[textIndex])
		{
			x = startX;
			y += font.height + lineSpacing;
			continue;
		}

		status = this->DrawChar(x, y, text[textIndex], font, fontColor, backgroundColor);
		if (Lcd::Error::Ok != status)
		{
			return status;
		}

		x -= (font.width + letterSpacing);
	}

	return Lcd::Error::Ok;
}

Lcd::Error LcdSsd1283a::ClearScreen(const uint16_t color)
{
	return this->DrawRectangle(0, 0, this->width, this->height, color);
}

