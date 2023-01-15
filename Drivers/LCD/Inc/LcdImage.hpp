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
#ifndef LCD_INC_LCDIMAGE_HPP_
#define LCD_INC_LCDIMAGE_HPP_

#include <stdint.h>

class LcdImage
{
public:
	const uint16_t width;
	const uint16_t height;
	const uint8_t * pixels;

private:
	static constexpr uint16_t pixelBytes = 2;
	static constexpr uint16_t msbMultiplier = 256;

public:
	bool GetPixel(const uint16_t x, const uint16_t y, uint16_t& pixelOut) const;
};

#endif /* LCD_INC_LCDIMAGE_HPP_ */
