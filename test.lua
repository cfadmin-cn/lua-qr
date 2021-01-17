local qr = require "qr"

local text = "https://cfadmin.cn"

qr.toPNG("1.png", text)
qr.toBMP("1.bmp", text)
qr.toSVG("1.svg", text)
qr.toJSON("1.JSON", text)
