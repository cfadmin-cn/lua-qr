#define LUA_LIB

#include <core.h>
#include "qr.h"

static int QR_VERSION = 10;
static int QR_MODE = QR_EM_8BIT;
static int QR_LEVEL = 2;
static int QR_TYPE = -1;

// 二维码白边边距
static int MAX_SEP = 5;
// 二维码内容大小
static int MAX_MAG = 10;

static inline QRCode* qr_init(const char* text, size_t *tsize) {
	int err = QR_ERR_NONE;

	QRCode *qr = qrInit(QR_VERSION, QR_MODE, QR_LEVEL, QR_TYPE, &err);
	if (!qr)
		return NULL;

	qrAddData(qr, (const qr_byte_t *)text, *tsize);

	if (!qrFinalize(qr)){
		qrDestroy(qr);
		return NULL;
	}

	return qr;
}

static inline int qr_writefile(const char * filename, char* buf, size_t bsize) {
	FILE *fp = fopen(filename, "wb");
	if (!fp) {
		free(buf);
		return 0;
	}
	// 写入内容到文件
	fwrite((const char*)buf, 1, bsize, fp); fflush(fp); fclose(fp); free(buf);
	return 1;
}

static inline qr_byte_t* qr_to_buffer(QRCode* qr, qr_format_t qr_fmt, int *wsize) {
	//两个5分别表示：像素之间的距离和二维码图片的放大倍数，范围都是1-16
	switch(qr_fmt) {
		case QR_FMT_PNG:
			return qrSymbolToPNG(qr, MAX_SEP, MAX_MAG, wsize);
		case QR_FMT_BMP:
			return qrSymbolToBMP(qr, MAX_SEP, MAX_MAG, wsize);
		case QR_FMT_SVG:
			return qrSymbolToSVG(qr, MAX_SEP, MAX_MAG, wsize);
		case QR_FMT_JSON:
			return qrSymbolToJSON(qr, MAX_SEP, MAX_MAG, wsize);
		default:
			return NULL;
	}
	return NULL;
} 


static int lwritePNG(lua_State *L) {
	const char* filename = luaL_checkstring(L, 1);
	size_t tsize = 0;
	QRCode *qr = qr_init(luaL_checklstring(L, 2, &tsize), &tsize);
	if (!qr)
		return luaL_error(L, "[QR ERROR]: Can't create QR object.");

	int wsize = 0;
	qr_byte_t *buffer = qr_to_buffer(qr, QR_FMT_PNG, &wsize);
	if (!buffer){
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: %s", qrGetErrorInfo(qr));
		qrDestroy(qr);
		return 2;
	}

	qrDestroy(qr);

	int ok = qr_writefile(filename, (char *)buffer, wsize);
	if (!ok) {
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: Failed to write to file[%s].", filename);
		return 2;
	}

	return 1;
}

static int lwriteBMP(lua_State *L) {
	const char* filename = luaL_checkstring(L, 1);
	size_t tsize = 0;
	QRCode *qr = qr_init(luaL_checklstring(L, 2, &tsize), &tsize);
	if (!qr)
		return luaL_error(L, "[QR ERROR]: Can't create QR object.");

	int wsize = 0;
	qr_byte_t *buffer = qr_to_buffer(qr, QR_FMT_BMP, &wsize);
	if (!buffer){
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: %s", qrGetErrorInfo(qr));
		qrDestroy(qr);
		return 2;
	}

	qrDestroy(qr);

	int ok = qr_writefile(filename, (char *)buffer, wsize);
	if (!ok) {
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: Failed to write to file[%s].", filename);
		return 2;
	}

	return 1;
}

static int lwriteSVG(lua_State *L) {
	const char* filename = luaL_checkstring(L, 1);
	size_t tsize = 0;
	QRCode *qr = qr_init(luaL_checklstring(L, 2, &tsize), &tsize);
	if (!qr)
		return luaL_error(L, "[QR ERROR]: Can't create QR object.");

	int wsize = 0;
	qr_byte_t *buffer = qr_to_buffer(qr, QR_FMT_SVG, &wsize);
	if (!buffer){
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: %s", qrGetErrorInfo(qr));
		qrDestroy(qr);
		return 2;
	}

	qrDestroy(qr);

	int ok = qr_writefile(filename, (char *)buffer, wsize);
	if (!ok) {
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: Failed to write to file[%s].", filename);
		return 2;
	}

	return 1;
}

static int lwriteJSON(lua_State *L) {
	const char* filename = luaL_checkstring(L, 1);
	size_t tsize = 0;
	QRCode *qr = qr_init(luaL_checklstring(L, 2, &tsize), &tsize);
	if (!qr) {
		return luaL_error(L, "[QR ERROR]: Can't create QR object.");
	}

	int wsize = 0;
	qr_byte_t *buffer = qr_to_buffer(qr, QR_FMT_JSON, &wsize);
	if (!buffer){
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: %s", qrGetErrorInfo(qr));
		qrDestroy(qr);
		return 2;
	}

	qrDestroy(qr);

	int ok = qr_writefile(filename, (char *)buffer, wsize);
	if (!ok) {
		lua_pushnil(L);
		lua_pushfstring(L, "[QR ERROR]: Failed to write to file[%s].", filename);
		return 2;
	}

	return 1;
}

static int lsetMAG(lua_State *L) {
	lua_Integer sep = luaL_checkinteger(L, 1);
	if (sep <= 0 || sep > QR_SEP_MAX)
		return luaL_error(L, "[QR ERROR]: `SEP` parameter must be greater than or equal to 1 and less than or equal to %d.", QR_SEP_MAX);
	MAX_SEP = sep;
	return 0;
}

static int lsetSEP(lua_State *L) {
	lua_Integer mag = luaL_checkinteger(L, 1);
	if (mag <= 0 || mag > QR_MAG_MAX)
		return luaL_error(L, "[QR ERROR]: `MAG` parameter must be greater than or equal to 1 and less than or equal to %d.", QR_MAG_MAX);
	MAX_MAG = mag;
	return 0;
}

static int lsetVERSION(lua_State *L) {
	lua_Integer version = luaL_checkinteger(L, 1);
	if (version < 1 || version > QR_VER_MAX)
		return luaL_error(L, "[QR ERROR]: `QR_VERSION` parameter must be greater than or equal to 1 and less than or equal to %d.", QR_VER_MAX);
	QR_VERSION = version;
	return 0;
}

static int lsetLEVEL(lua_State *L) {
	lua_Integer level = luaL_checkinteger(L, 1);
	if (level < QR_ECL_L || level > QR_ECL_H)
		return luaL_error(L, "[QR ERROR]: `QR_LEVEL` parameter must be greater than or equal to %d and less than or equal to %d.", QR_ECL_L, QR_ECL_H);
	QR_LEVEL = level;
	return 0;
}

static int lsetTYPE(lua_State *L) {
	lua_Integer type = luaL_checkinteger(L, 1);
	if (type < -1 || type >= QR_MPT_MAX)
		return luaL_error(L, "[QR ERROR]: `QR_TYPE` parameter must be greater than or equal to %d and less than or equal to %d.", -1, QR_MPT_MAX);
	QR_TYPE = type;
	return 0;
}

LUAMOD_API int luaopen_qr(lua_State* L) {
	luaL_checkversion(L);
	luaL_Reg qr_libs[] = {
		{ "toPNG", lwritePNG },
		{ "toBMP", lwriteBMP },
		{ "toSVG", lwriteSVG },
		{ "toJSON", lwriteJSON },

		// 全局配置
		{ "setMAG", lsetMAG },
		{ "setSEP", lsetSEP },
		{ "setTYPE", lsetTYPE },
		{ "setLEVEL", lsetLEVEL },
		{ "setVERSION", lsetVERSION },
		{ NULL, NULL }
	};

	luaL_newlib(L, qr_libs);
	return 1;
}
