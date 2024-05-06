# बोसजी की पीस्ट्रिंग लाइब्रेरी

> कृतसंकल्प मुद्रण कारक संयोग।

> ***एक रचनात्मक भारतीय उत्पाद।***

## Boseji's PString Library

> (Print to String Library.)

**`bosejis_PString`** *("Print to String Library")* is a new lightweight Print-derivative string class that renders text into a character buffer `char[]`.

With ***bosejis_PString***, you can use the Print renderer for any device, even those that do not directly support Print-style text formatting, by first "printing" to a `char[]` array.

For Better documentation Refer to :

<http://arduiniana.org/libraries/pstring/>

This is the 3rd Version of the library

## Installation

### Using [Zip File](https://github.com/ardlib/bosejis_PString/archive/refs/heads/main.zip) from this repository

Downloading the Zip file of this repository from :

<https://github.com/ardlib/bosejis_PString/archive/refs/heads/main.zip>

And installing using the **Add .ZIP Library** feature:

- For **Arduino IDE 1.8.19** and above:
    
    Go to Menu `Sketch -> Include Library -> Add .ZIP Library`

## Usage

### Basic Usage of `bosejis_PString`

In its simplest use case, you deploy an "on-the-fly" constructor to format text:

```c++
char buffer[30];
#define pi 3.14159
PString(buffer, sizeof(buffer), pi);
```

This code uses Print’s float rendering functions to generate the string equivalent of `pi` into buffer.

Since **`PString`** inherits from `Print`, **`PString`** objects can do everything that other Print-derived classes do:

```c++
char buffer[50];
PString mystring(buffer, sizeof(buffer));
char name[] = "Joe";
int age = 45;

mystring.print("Hi, my name is ");
mystring.print(name);
mystring.print(" and I am ");
mystring.print(age);
mystring.println(" years old.");
Serial.print(buffer); // Directly access the internal buffer.
```

This generates the expected sentence in buffer the same as if you had *printed* to the Serial port.


### String like functions of `bosejis_PString`

**`PString`** is a fairly minimal string class. It can report its length and capacity and give const access to its internal string buffer:

```c++
Serial.print(mystring.length());
Serial.print(mystring.capacity());
Serial.print(mystring);
```

You can reuse a string by calling its `begin()` function. This effectively resets the position in the buffer where the next printed text will go:

```c++
mystring.begin();
mystring.print("Hari");
mystring.begin();
mystring.print("Aum");
// mystring contains "Aum" here
```

### Operators support of `bosejis_PString`

**`PString`** provides three operators for assignment, concatenation, and equivalency test:

```c++
char buffer[20];
PString str(buffer, sizeof(buffer));
str = "Namo"; // assignment
str += " Namh!"; // concatenation
if (str == "Namo Namh!") // comparison
{
    Serial.println("They are equal!");
}
```

### Runtime safety of `bosejis_PString`

***`PStrings`*** do not “own” their own buffers.

Instead, they rely on **pre-allocated static buffers** that are passed in at the point of construction.

***`PStrings` never allocate memory dynamically***, even when the result of a `print()`, assignment, or concatenation operation would seem to exceed the current buffer’s size.

*In these cases, the excess data is simply discarded and the string correctly terminated.*

Because of these constraints, ***`bosejis_PString`*** can make three key guarantees:

>
> **1. They will never cause a buffer overflow**
>
> **2. A string’s buffer will always be valid memory, i.e. the original buffer**
>
> **3. buffers will always contain valid (i.e. NULL-terminated) C string data.**
>

## Resource Consumption of `bosejis_PString`

**`PString`** objects consume 8 bytes of memory during their lifetimes.
Depending on what features are used, including the **`bosejis_PString`** library
usually adds only `100-600 bytes` to a *program’s size*.

> *[All input is appreciated](http://arduiniana.org/libraries/pstring/).*
>
> [Mikal Hart](http://arduiniana.org/about/)

## Revision History

- Version 1 – initial release by Mikal Hart
- Version 2 – include support for inline renderings with modifiers HEX, OCT, etc.
    (and eventually float precision) by Mikal Hart
- Version 3 – Arduino 1.0 compatibility by Mikal Hart
- V3.0.1 - Adding Hex printing functions and Arduino Library integrations by boseji
- V3.0.2 - Adding CI/CD build verification by boseji
- Library Taken down in early Q1'2021.
- Revival under different name, License and context.
- Refer to [Releases](https://github.com/ardlib/bosejis_PString/releases/latest) to understand.
- Cleanup Command `clang-format -i src/*.h src/*.cpp examples/basic_use/basic_use.ino`

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new Functions & Features

Please read [CONTRIBUTING.md](https://github.com/ardlib/bosejis_PString/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

This library has been created by [Mikal Hart](http://arduiniana.org/about/).

This is only a github-fork of the project.

It is being improved upon, here by [@boseji](https://github.com/boseji).

### Original Works

The **Original version** of **`PString`** is [PString3.zip](http://arduiniana.org/PString/PString3.zip).

## License

`SPDX: GPL-3.0-or-later`

`bosejis_PString` - Print to String Library

Copyright (C) 2009-2012 Mikal Hart.
Copyright (C) 2020-2024 by Abhijit Bose (aka. Boseji)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.