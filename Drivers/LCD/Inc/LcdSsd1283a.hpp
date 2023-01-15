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
#ifndef LCD_INC_LCDSSD1283A_HPP_
#define LCD_INC_LCDSSD1283A_HPP_

#include "Lcd.hpp"
#include "LcdCom.hpp"

class LcdSsd1283a : public Lcd
{
	class Registers
	{
	public:
		/** Memory address for "Oscillator" register */
		static constexpr uint8_t OSCILLATION 					 			= 0x00;
		/** Memory address for "Driver Output Control" register */
		static constexpr uint8_t DRIVER_OUTPUT_CTRL             			= 0x01;
		/** Memory address for "LCD-Driving-Waveform Control" register */
		static constexpr uint8_t DRIVER_AC_CTRL                 			= 0x02;
		/** Memory address for "Entry Mode" register */
		static constexpr uint8_t ENTRY_MODE                     			= 0x03;
		/** Memory address for "Compare Register 1" register */
		static constexpr uint8_t CMP_1                      	 			= 0x04;
		/** Memory address for "Compare Register 2" register */
		static constexpr uint8_t CMP_2                      	 			= 0x05;
		/** Memory address for "Display Control" Register */
		static constexpr uint8_t DISPLAY_CTRL                   			= 0x07;
		/** Memory address for "Frame Cycle Control" register */
		static constexpr uint8_t FRAME_CYCLE_CTRL               			= 0x0B;
		/** Memory address for "Power Control 1" register */
		static constexpr uint8_t POWER_CTRL_1                   			= 0x10;
		/** Memory address for "Power Control 2" register */
		static constexpr uint8_t POWER_CTRL_2                   			= 0x11;
		/** Memory address for "Power Control 3" register */
		static constexpr uint8_t POWER_CTRL_3                   			= 0x12;
		/** Memory address for "Power Control 4" register */
		static constexpr uint8_t POWER_CTRL_4                   			= 0x13;
		/** Memory address for "Horizontal Porch" register */
		static constexpr uint8_t HORIZONTAL_PORCH               			= 0x16;
		/** Memory address for "Vertical Porch" register */
		static constexpr uint8_t VERTICAL_PORCH                 			= 0x17;
		/** Memory address for "Power Control 5" register */
		static constexpr uint8_t POWER_CTRL_5                   			= 0x1E;
		/** Memory address for "Power Control 6" register */
		static constexpr uint8_t POWER_CTRL_6                   			= 0x1F;
		/** Memory address for "RAM Address Set" register */
		static constexpr uint8_t RAM_SET                        			= 0x21;
		/** Memory address for "Write Data to GRAM" register */
		static constexpr uint8_t RAM_WRITE                      			= 0x22;
		/** Memory address for "Read Data from GRAM" register */
		static constexpr uint8_t RAM_READ                       			= 0x22;
		/** Memory address for "RAM Write Data Mask 1" register */
		static constexpr uint8_t RAM_WRITE_MASK_1               			= 0x23;
		/** Memory address for "RAM Write Data Mask 2" register */
		static constexpr uint8_t RAM_WRITE_MASK_2               			= 0x24;
		/** Memory address for "Vcom OTP 1" register */
		static constexpr uint8_t VCOM_OTP_1                     			= 0x28;
		/** Memory address for "Vcom OTP 2" register */
		static constexpr uint8_t VCOM_OTP_2                     			= 0x29;
		/** Memory address for "Gamma Control 1" register */
		static constexpr uint8_t GAMMA_CTRL_01                  			= 0x30;
		/** Memory address for "Gamma Control 2" register */
		static constexpr uint8_t GAMMA_CTRL_02                  			= 0x31;
		/** Memory address for "Gamma Control 3" register */
		static constexpr uint8_t GAMMA_CTRL_03                  			= 0x32;
		/** Memory address for "Gamma Control 4" register */
		static constexpr uint8_t GAMMA_CTRL_04                  			= 0x33;
		/** Memory address for "Gamma Control 5" register */
		static constexpr uint8_t GAMMA_CTRL_05                  			= 0x34;
		/** Memory address for "Gamma Control 6" register */
		static constexpr uint8_t GAMMA_CTRL_06                  			= 0x35;
		/** Memory address for "Gamma Control 7" register */
		static constexpr uint8_t GAMMA_CTRL_07                  			= 0x36;
		/** Memory address for "Gamma Control 8" register */
		static constexpr uint8_t GAMMA_CTRL_08                  			= 0x37;
		/** Memory address for "Gamma Control 9" register */
		static constexpr uint8_t GAMMA_CTRL_09                  			= 0x38;
		/** Memory address for "Gamma Control 10" register */
		static constexpr uint8_t GAMMA_CTRL_10                  			= 0x39;
		/** Memory address for "Gate Scan Position" register */
		static constexpr uint8_t GATE_SCAN                      			= 0x40;
		/** Memory address for "Vertical Scroll Control" register */
		static constexpr uint8_t VERTICAL_SCROLL_CTRL           			= 0x41;
		/** Memory address for "1st Screen Driving Position" register */
		static constexpr uint8_t DISPLAY_1ST                    			= 0x42;
		/** Memory address for "2nd Screen Driving Position" register */
		static constexpr uint8_t DISPLAY_2ND                    			= 0x43;
		/** Memory address for "Horizontal RAM Address Position" register */
		static constexpr uint8_t HORIZONTAL_RAM_SET             			= 0x44;
		/** Memory address for "Vertical RAM Address Position" register */
		static constexpr uint8_t VERTICAL_RAM_SET               			= 0x45;
	};
	class RegisterValues
	{
	public:
		/** The most significant byte value for "Display Control" register in the *first* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON1_MSB          		= 0x00;
		/** The least significant byte value for "Display Control" register in the *first* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON1_LSB				= 0x21;

		/** The most significant byte value for "Oscillator" register to turn on LCD SSD1283A display */
		static constexpr uint8_t OSCILLATION_DISPLAYON_MSB					= 0x00;
		/** The least significant byte value for "Oscillator" register to turn on LCD SSD1283A display */
		static constexpr uint8_t OSCILLATION_DISPLAYON_LSB					= 0x01;

		/** The most significant byte value for "Display Control" register in the *second* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON2_MSB				= 0x00;
		/** The least significant byte value for "Display Control" register in the *second* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON2_LSB				= 0x23;

		/** The most significant byte value for "Power Control 1" register to turn on LCD SSD1283A display */
		static constexpr uint8_t POWER_CTRL_1_DISPLAYON_MSB					= 0x2F;
		/** The least significant byte value for "Power Control 1" register to turn on LCD SSD1283A display */
		static constexpr uint8_t POWER_CTRL_1_DISPLAYON_LSB					= 0xC4;

		/** The most significant byte value for "Display Control" register in the *third* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON3_MSB				= 0x00;
		/** The least significant byte value for "Display Control" register in the *third* step to turn on LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYON3_LSB				= 0x33;

		/** The most significant byte value for "Driver Output Control" register to initialize LCD SSD1283A display */
		static constexpr uint8_t DRIVER_OUTPUT_CTRL_INIT_MSB				= 0x23;
		/** The least significant byte value for "Driver Output Control" register to initialize LCD SSD1283A display */
		static constexpr uint8_t DRIVER_OUTPUT_CTRL_INIT_LSB				= 0x83;

		/** The most significant byte value for "Entry Mode" register to initialize LCD SSD1283A display */
		static constexpr uint8_t ENTRY_MODE_INIT_MSB						= 0x68;
		/** The least significant byte value for "Entry Mode" register to initialize LCD SSD1283A display */
		static constexpr uint8_t ENTRY_MODE_INIT_LSB						= 0x20;

		/** The most significant byte value for "LCD-Driving-Waveform Control" register to initialize LCD SSD1283A display */
		static constexpr uint8_t DRIVER_AC_CTRL_INIT_MSB					= 0x00;
		/** The least significant byte value for "LCD-Driving-Waveform Control" register to initialize LCD SSD1283A display */
		static constexpr uint8_t DRIVER_AC_CTRL_INIT_LSB					= 0x00;

		/** The most significant byte value for "Display Control" register to turn off LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYOFF_MSB				= 0x00;
		/** The least significant byte value for "Display Control" register to turn off LCD SSD1283A display */
		static constexpr uint8_t DISPLAY_CTRL_DISPLAYOFF_LSB				= 0x00;

		/** The most significant byte value for "Oscillator" register to turn off LCD SSD1283A display */
		static constexpr uint8_t OSCILLATION_DISPLAYOFF_MSB					= 0x00;
		/** The least significant byte value for "Oscillator" register to turn off LCD SSD1283A display */
		static constexpr uint8_t OSCILLATION_DISPLAYOFF_LSB					= 0x00;

		/** The most significant byte value for "Power Control 1" register to turn off LCD SSD1283A display */
		static constexpr uint8_t POWER_CTRL_1_DISPLAYOFF_MSB				= 0x00;
		/** The least significant byte value for "Power Control 1" register to turn off LCD SSD1283A display */
		static constexpr uint8_t POWER_CTRL_1_DISPLAYOFF_LSB				= 0x01;
	};

	static constexpr uint16_t width 																= 132;
	static constexpr uint16_t height 																= 132;
	static constexpr uint16_t resetUs 																= 15;

	static constexpr uint16_t dataSize																= 2;
	static constexpr uint16_t commandHandleSize														= 3;

	/** Array of commands (command code + data) to turn on the LCD SSD1283A display */
	static uint8_t displayOnCommands[][commandHandleSize];
	/** Array of commands (command code + data) to turn off the LCD SSD1283A display */
	static uint8_t displayOffCommands[][commandHandleSize];
	/** Array of commands (command code + data) to initialize LCD SSD1283A controller properties */
	static uint8_t initCommands[][commandHandleSize];

	Lcd::Error SendSetOfCommands(uint8_t commands[][LcdSsd1283a::commandHandleSize], const size_t numberOfRows) const;
	Lcd::Error DrawChar(const uint8_t x, const uint8_t y, const char character,
			const LcdFont& font, const uint16_t fontColor, const uint16_t backgroundColor) const;
	Lcd::Error InitWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height) const;

public:
	LcdSsd1283a(LcdSpi& spiCom);
	~LcdSsd1283a();
	Lcd::Error DisplayOn();
	Lcd::Error DisplayOff();
	Lcd::Error DrawRectangle(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, const uint16_t color);
	Lcd::Error DrawImage(const uint16_t x, const uint16_t y, const LcdImage& image);
	Lcd::Error DrawText(uint16_t x, uint16_t y, std::string text,
		  const int16_t letterSpacing, const int16_t lineSpacing, const LcdFont& font,
		  const uint16_t fontColor, const uint16_t backgroundColor);
	Lcd::Error ClearScreen(const uint16_t color);
};

#endif /* LCD_INC_LCDSSD1283A_HPP_ */
