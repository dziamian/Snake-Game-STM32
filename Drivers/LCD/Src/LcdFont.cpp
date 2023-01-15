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
#include "LcdFont.hpp"

bool LcdFont::GetLine(const char character, const uint16_t lineIndex, const uint16_t y, uint8_t& lineOut) const
{
	uint16_t characterIndex;
	if (!this->GetCharacterIndex(character, characterIndex))
	{
		return false;
	}

	if (lineIndex * LcdFont::byteLine >= this->width || y >= this->height)
	{
		return false;
	}

	lineOut = this->pixelMap[characterIndex * this->lines * this->height + y * this->lines + lineIndex];
	return true;
}

bool LcdFont::GetCharacterIndex(const char character, uint16_t& indexOut) const
{
	indexOut = character - this->firstCharacter;
	return indexOut < this->characters;
}

bool LcdFont::GetPixel(const char character, const uint16_t x, const uint16_t y, bool& pixelOut) const
{
	uint8_t line;
	if (!this->GetLine(character, x / LcdFont::byteLine, y, line))
	{
		return false;
	}

	pixelOut = !!(line & (LcdFont::firstPixelMask >> (x % LcdFont::byteLine)));
	return true;
}
