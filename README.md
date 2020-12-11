# lua-qr

	Lua QR Code Generation Library

## Introduction

	Advantage:

	* The QR code generation library based on C language is currently bound to Lua language export API.

	* A single API can be used to generate formats such as PNG/BMP/SVG/JSON.

	* Developers can customize configuration through the global API.

	Disadvantage:

	* Not suitable for very frequent QR code file generation scenarios.

	* Large memory usage.

## User's Guidance

	After successfully importing the library with `local qr = require "qr"` program code, you can use the following API:

	* qr.toPNG(filename, text) - Write the content of `text` into the file of `filename` in PNG format; if writing is successful, return `true`, otherwise it will return: false、 errorinfo;

	* qr.toSVG(filename, text) - Write the content of `text` into the file of `filename` in SVG format; if writing is successful, return `true`, otherwise it will return: false、 errorinfo;

	* qr.toBMP(filename, text) - Write the content of `text` into the file of `filename` in BMP format; if writing is successful, return `true`, otherwise it will return: false、 errorinfo;

	* qr.toJSON(filename, text) - Write the content of `text` into the file of `filename` in JSON format; if writing is successful, return `true`, otherwise it will return: false、 errorinfo;

## LICENSE

	[MIT-LICENSE](https://github.com/CandyMi/lua-qr/blob/master/LICENSE)