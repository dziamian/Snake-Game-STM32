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
#ifndef LCD_INC_LCD_HPP_
#define LCD_INC_LCD_HPP_

#include <stdint.h>
#include <string>

#include "LcdCom.hpp"
#include "LcdImage.hpp"
#include "LcdFont.hpp"

class Lcd
{
	const uint16_t width;
	const uint16_t height;

protected:
	LcdCom * const com;

public:

	enum class Error : int
	{
		Ok,
		InvalidArgument,
		InvalidOperation,
		InvalidResource,
		CommunicationFailed
	};

	Lcd(const uint16_t width, const uint16_t height, LcdCom& com);
	uint16_t GetWidth() const;
	uint16_t GetHeight() const;
	virtual ~Lcd() = 0;
	virtual Error DisplayOn() = 0;
	virtual Error DisplayOff() = 0;
	virtual Error DrawRectangle(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, const uint16_t color) = 0;
	virtual Error DrawImage(const uint16_t x, const uint16_t y, const LcdImage& image) = 0;
	virtual Error DrawText(uint16_t x, uint16_t y, std::string text,
	        const int16_t letterSpacing, const int16_t lineSpacing, const LcdFont& font,
	        const uint16_t fontColor, const uint16_t backgroundColor) = 0;
	virtual Error ClearScreen(const uint16_t color) = 0;
};

#endif /* LCD_INC_LCD_HPP_ */
