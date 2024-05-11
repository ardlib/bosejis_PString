/**
 * bosejis_PString.h - Print to String Library
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

#ifndef bosejis_PString_h
#define bosejis_PString_h

#include "Print.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PSTRING_LIBRARY_VERSION 0

class PString : public Print {
private:
  char *_buf, *_cur;
  size_t _size;

public:
#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif

public:
  // Basic constructor requires a preallocated buffer
  PString(char *buf, size_t size) : _buf(buf), _size(size) { begin(); }

  // templated constructors allow inline renderings of this type:
  //    PString(buf, size, myfloat[, modifier]);
  template <class T>
  PString(char *buf, size_t size, T arg) : _buf(buf), _size(size) {
    begin();
    print(arg);
  }

  template <class T>
  PString(char *buf, size_t size, T arg, int modifier)
      : _buf(buf), _size(size) {
    begin();
    print(arg, modifier);
  }

  // returns the length of the current string, not counting the 0 terminator
  inline size_t length() { return _cur - _buf; }

  // returns the capacity of the string
  inline size_t capacity() { return _size; }

  // gives access to the internal string
  inline operator const char *() { return _buf; }
  inline const char *c_str() { return (const char *)_buf; }

  // compare to another string
  bool operator==(const char *str) { return _size > 0 && !strcmp(_buf, str); }

  // call this to re-use an existing string
  void begin();

  // This function allows assignment to an arbitrary scalar value like
  //    str = myfloat;
  template <class T> inline PString &operator=(T arg) {
    begin();
    print(arg);
    return *this;
  }

  // Concatenation of any type data
  //    str += myfloat;
  template <class T> inline PString &operator+=(T arg) {
    print(arg);
    return *this;
  }

  // Safe access to sprintf-like formatting,
  // e.g. str.format("Hi, my name is %s and I'm %d years old", name, age);
  int format(const char *str, ...);

  // Print Hex value to the String

  int Hex(uint8_t data);
  int Hex(char data);
  int Hex(uint16_t data);
  int Hex(int16_t data);
  int Hex(uint32_t data);
  int Hex(int32_t data);
  int Hex(uint64_t data);
  int Hex(int64_t data);
  int Hex(bool data);
  int Hex(float data);
  int Hex(double data);
  template <class T> inline int Hex(T *arg) {
    // Print the Memory Address
    return Hex((uint64_t)arg);
  }

  // Print a Hex Buffer to the String
  template <class T> inline int HexBuffer(T *arg, size_t size) {
    int ret = 0;
    for (size_t i = 0; i < size; i++) {
      ret += Hex(arg[i]);
    }
    return ret;
  }

  // Print a Hex Buffer like C Array to the String
  template <class T> inline int HexArray(T *arg, size_t size) {
    int ret = 0;
    for (size_t i = 0; i < size; i++) {
      ret += print(F(" 0x"));
      ret += Hex(arg[i]);
      if (i < (size - 1)) {
        ret += print(',');
      }
    }
    return ret;
  }
};

#endif /* bosejis_PString_h */
