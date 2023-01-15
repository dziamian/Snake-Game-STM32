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
#ifndef LCD_INC_LCDFONT_HPP_
#define LCD_INC_LCDFONT_HPP_

#include <stdint.h>

class LcdFont
{
public:
	const uint16_t width;
	const uint16_t height;
	const char firstCharacter;
	const uint16_t characters;
	const uint8_t * pixelMap;

	const uint16_t lines;
	const uint16_t fullLines;
	const uint16_t lastLine;

private:
	static constexpr uint16_t firstPixelMask = 0x80;

public:
	static constexpr uint16_t byteLine = 8;

private:
	bool GetLine(const char character, const uint16_t lineIndex, const uint16_t y, uint8_t& lineOut) const;
	bool GetCharacterIndex(const char character, uint16_t& indexOut) const;

public:
	bool GetPixel(const char character, const uint16_t x, const uint16_t y, bool& pixelOut) const;
};

#endif /* LCD_INC_LCDFONT_HPP_ */
