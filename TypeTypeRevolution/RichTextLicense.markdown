## About
This RichText class aims to fix problems present in existing implementations; namely issues with spacing and lack of support for newlines.
It also places an emphasis on data rather than code; currently it uses a minimal markup syntax instead of using C++ streams.

## Usage
Please see the included example program for usage. The API is nearly a direct copy of sf::Text, and RichText instances can be used in the same way as any other Drawable class.

## Markup
**Bold** text is denoted by surrounding a string with asterisks: \*like this\*.

*Italic* text is denoted by surrounding a string with tildes: ~like this~.

Underlined text is denoted by surrounding a string with underscores: \_like this\_.


Text color is set with the hash character (#) followed by a hex code or color name. The tag runs until the next whitespace character.
Both of these forms are equivalant: #red ,#ff0000 .

Please see source.txt for a demonstration of all markup features.

## License
Copyright (c) 2012 Jacob Albano

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.