/**
 * bosejis_PString.cpp - Print to String Library
 *
 * बोसजी की पीस्ट्रिंग लाइब्रेरी
 * ===============================
 * कृतसंकल्प मुद्रण कारक संयोग।
 *
 * एक रचनात्मक भारतीय उत्पाद।
 *
 * Boseji's PString Library
 * (Print to String Library.)
 *
 * Sources
 * -------
 * https://github.com/ardlib/bosejis_PString
 *
 * License
 * --------
 * SPDX: GPL-3.0-or-later
 *
 *  bosejis_PString - Print to String Library
 *  Copyright (C) 2009-2012 Mikal Hart.
 *  Copyright (C) 2020-2024 by Abhijit Bose (aka. Boseji)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "bosejis_PString.h"

void PString::begin() {
  _cur = _buf;
  if (_size > 0)
    _buf[0] = '\0';
}

#if defined(ARDUINO) && ARDUINO >= 100
size_t PString::write(uint8_t b)
#else
void PString::write(uint8_t b)
#endif
{
  if (_cur + 1 < _buf + _size) {
    *_cur++ = (char)b;
    *_cur = '\0';
#if defined(ARDUINO) && ARDUINO >= 100
    return 1;
#endif
  }

#if defined(ARDUINO) && ARDUINO >= 100
  return 0;
#endif
}

int PString::format(char *str, ...) {
  va_list argptr;
  va_start(argptr, str);
  int ret = vsnprintf(_cur, _size - (_cur - _buf), str, argptr);
  if (_size)
    while (*_cur)
      ++_cur;
  return ret;
}

int PString::Hex(uint8_t data) {
  static const char map[] = {"0123456789abcdef"};
  int ret;
  ret = print(map[(uint8_t)((data & 0xF0) >> 4)]);
  ret += print(map[(uint8_t)(data & 0x0F)]);
  return ret;
}

int PString::Hex(char data) { return Hex((uint8_t)data); }

int PString::Hex(uint16_t data) {
  int ret;
  ret = Hex((uint8_t)((data >> 8) & 0xFFU));
  ret += Hex((uint8_t)((data >> 0) & 0xFFU));
  return ret;
}

int PString::Hex(int16_t data) { return Hex((uint16_t)data); }

int PString::Hex(uint32_t data) {
  int ret;
  ret = Hex((uint16_t)((data >> 16) & 0xFFFFU));
  ret += Hex((uint16_t)((data >> 0) & 0xFFFFU));
  return ret;
}

int PString::Hex(int32_t data) { return Hex((uint32_t)data); }

int PString::Hex(uint64_t data) {
  int ret;
  ret = Hex((uint32_t)((data >> 32) & 0xFFFFU));
  ret += Hex((uint32_t)((data >> 0) & 0xFFFFU));
  return ret;
}

int PString::Hex(int64_t data) { return Hex((uint64_t)data); }

// int PString::Hex(size_t data) { return Hex((uint32_t)data); }

int PString::Hex(bool data) { return Hex((uint8_t)data); }

int PString::Hex(float data) { return Hex((uint32_t)data); }

int PString::Hex(double data) { return Hex((uint64_t)data); }