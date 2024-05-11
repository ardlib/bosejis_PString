/**
 * Basic Usage Example.
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
#include <bosejis_PString.h>

// Defines
#define SEPARATOR()                                                            \
  Serial.println(F("\n----------------------------------------------------"))
#define LONG_STRING                                                            \
  "bosejis_PString (\"Print to String Library\") is a new lightweight "        \
  "Print-derivative string class that renders text into a character buffer "   \
  "`char[]`."

// Functions
void Test_Basic();
void Test_Format();
void Test_Hex();

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  delay(1000);
}

void loop() {
  Test_Basic();
  delay(5000);
  Test_Format();
  delay(5000);
  Test_Hex();
  delay(5000);
}

void Test_Basic() {
#define TEST_BASIC_BUF 50
#define SECS 86400
  char buffer[TEST_BASIC_BUF];
  SEPARATOR();
  Serial.println(F("Quick Conversion Examples."));
  Serial.println();
  // There are two main ways to use a PString.
  // First, the "quickie" way, simply renders a single value into a buffer
  PString(buffer, sizeof(buffer), PI, 7); // print the value of PI into the buffer
  Serial.print(F("Printing a Floating Point: "));
  Serial.println(buffer); // do whatever you want with "buffer" here.
  Serial.println();

  // Other "quickie" examples:

  PString(buffer, sizeof(buffer), "Printing strings");
  Serial.print(F("Normal String: "));
  Serial.println(buffer);
  Serial.println();

  PString(buffer, sizeof(buffer), SECS);
  Serial.print(F("Numeric Value: "));
  Serial.println(buffer);
  Serial.println();

  PString(buffer, sizeof(buffer), SECS, HEX);
  Serial.print(F("Numeric Value in default Hex format: 0x"));
  Serial.println(buffer);
  Serial.println();

  // You can also created a (named) PString object and operate
  // on it exactly as you would with Serial or LiquidCrystal
  PString str(buffer, sizeof(buffer));
  str.print("The value of PI is ");
  str.print(PI, 7);

  // At this point, buffer contains "The value of PI is 3.14.."
  // You can get to the data directly...
  Serial.println(F("Directly from Buffer : "));
  Serial.println(buffer);
  Serial.println();
  // ... or indirectly
  Serial.println(F("Indirect from PString: "));
  Serial.println(str);
  Serial.println();

  // There are a couple of useful member functions:
  Serial.print(F("The string's length is "));
  Serial.println(str.length());
  Serial.print(F("Its capacity is "));
  Serial.println(str.capacity());
  Serial.println();

  // You can reuse a PString with the begin() function
  str.begin();
  str.print("Hari Aum");
  Serial.println(F("Reusing PString: "));
  Serial.println(str);
  Serial.println();

  // Or accomplish the same thing with the assignment operator:
  str = "Aum Namh";

  // PStrings support the concatenation operator
  str += " Shivay!";
  Serial.println(F("Assignment to PString and Concatenation: "));
  Serial.println(str);
  Serial.println();

  // And you can also check for equivalence
  if (str == "Aum Namh Shivay!") {
    Serial.println(F("This value is indeed correct and equivalent!"));
  }
  Serial.println();

  // PString will safely auto terminate the Strings
  Serial.println(F("A Very long string: "));
  Serial.println(F(LONG_STRING));
  Serial.println();
  // Now we do a PString print
  PString(buffer, sizeof(buffer), LONG_STRING);
  Serial.println(F("Here is how it looks in PString (Auto-Terminated): "));
  Serial.println(buffer);
  Serial.println();
  Serial.println(F("No more buffer overflows!"));
  Serial.println();
}

void Test_Format() {
#define TEST_FORMAT_BUF 100
  char buffer[TEST_FORMAT_BUF];
  SEPARATOR();
  Serial.println(F("Formatting Examples."));
  Serial.println();

  // Here is how what sprintf looks like for PString
  PString str(buffer, sizeof(buffer));
  str.format("Formatted Floating point looks like: %04.7f", PI);
  Serial.println(buffer);
  Serial.println(F("This might not get printed in some Architectures."));
  Serial.println();
  str.begin();
  str.print(F("A Batter way to print floating points: "));
  str.print(PI, 7);
  Serial.println(buffer);
  Serial.println();

  // Other Things do work here
  str.begin();
  str.format("Printing %08lu Integers work but %08X Hex does not.",
             (uint64_t)25693921, (uint64_t)0x3242569CDU);
  Serial.println(buffer);
  Serial.println();

  str.begin();
  str.format("Printing String '%s' works fine too.", "Ram Ram");
  Serial.println(buffer);
  Serial.println();
}

void Test_Hex() {
#define TEST_HEX_BUF 100
  char buffer[TEST_HEX_BUF];
  uint32_t u32test = 20;
  const char *buf = "Hari Aum";
  SEPARATOR();
  Serial.println(F("Hex Printing Examples."));
  Serial.println();

  PString str(buffer, sizeof(buffer));
  // We can Easily Print characters and their Hex:
  str.print(F("Tab Character '\\t' is 0x"));
  str.Hex('\t');
  Serial.println(str.c_str());
  Serial.println();

  str.begin();
  str.print(F("Boolean Value of 'True' is 0x"));
  str.Hex(true);
  Serial.println(str);
  Serial.println();

  str.begin();
  str.print(F("uint64_t Value of '1311768467294899695' is 0x"));
  str.Hex((uint64_t)0x1234567890123456);
  Serial.println(str);
  Serial.println();

  str.begin();
  str.print(F("Floating Point Value of PI is "));
  str.print(PI, 7);
  str.print(F(" And in Hex 0x"));
  str.Hex(PI);
  Serial.println(str);
  Serial.println();

  str.begin();
  str.print(F("We can also print Address of Variables : 0x"));
  str.Hex(&u32test);
  Serial.println(str);
  Serial.println();

  str.begin();
  str.format("We can print Buffers '%s' : 0x", buf);
  str.HexBuffer(buf, strlen(buf));
  Serial.println(str);
  Serial.println();

  str.begin();
  str.format("Or in Array Form '%s' : {", buf);
  str.HexArray(buf, strlen(buf));
  str.print(F(" }"));
  Serial.println(str);
  Serial.println();
}