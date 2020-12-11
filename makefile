.PHONY : build clean

default :
	@echo "======================================="
	@echo "Please use 'make build' command to build it.."
	@echo "Please use 'make clean' command to clean all."
	@echo "======================================="

# CFLAGS = -O3 -w -shared -fPIC -ljemalloc
# CFLAGS = -O3 -w -shared -fPIC -ltcmalloc
CFLAGS = -O3 -w -shared -fPIC
CC = cc

INCLUDES = -I./ -I../ -I../../ -I../../../ -I/usr/local/include
LIBS = -L./ -L../ -L../../ -L../../../ -L/usr/local/lib
DLL = -lcore -llua -lz

build:
	@$(CC) -o qr.so luaqr.c qr.c qrcnv.c qrcnv_bmp.c qrcnv_png.c qrcnv_svg.c qrcnv_tiff.c $(INCLUDES) $(LIBS) $(CFLAGS) $(DLL)
	@mv *.so ../

clean:
	rm -rf main qr.so
