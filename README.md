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


## Installation

  * Use the `git clone` command to clone the code into the `3rd` directory of the framework.

  * Finally, use the `make build` command to compile the code without errors, then you can start using it in the project.

## User's Guidance

  After successfully importing the library with `local qr = require "qr"` program code, you can use the following API:

  * qr.toPNG(filename, text)

	* qr.toSVG(filename, text)

	* qr.toBMP(filename, text)

	* qr.toJSON(filename, text)

	The above `API` is used to write the content of the `text` parameter into the path file indicated by `filename` in the specified format, the format can be: `JSON`/`PNG`/`SVG`/`BMP`;

	* qr.setMAG(mag) - QR Image margins.

	* qr.setSEP(sep) - QR Pixel magnification.

	* qr.setVERSION(version) - QR Version.

	* qr.setLEVEL(level) - QR Error correction level.

	* qr.setTYPE(type) - QR Mask pattern type.

	The above method is a global configuration, and developers will use the above method to modify it will take effect globally.

	Please refer to the `test.lua` file for specific sample codes.

## LICENSE

  [MIT-LICENSE](https://github.com/CandyMi/lua-qr/blob/master/LICENSE)