local LOG = require "logging"

local qr = require "qr"

local text = "https://cfadmin.cn"

LOG:DEBUG(qr)

qr.toPNG("1.png", text)
qr.toBMP("1.bmp", text)
qr.toSVG("1.svg", text)
qr.toJSON("1.JSON", text)