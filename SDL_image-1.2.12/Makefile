# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2
CFLAGS += -DLOAD_BMP -DLOAD_PNG
CFLAGS += $(SDL_INCLUDE)
# -I../libpng
CFLAGS += -I../lpng157 -I../zlib-1.2.5
CPPFLAGS := $(CFLAGS)

TARGET := libSDL_image.a

OBJECTS := 
OBJECTS += IMG.o
OBJECTS += IMG_bmp.o
OBJECTS += IMG_gif.o
OBJECTS += IMG_jpg.o
OBJECTS += IMG_lbm.o
OBJECTS += IMG_pcx.o
OBJECTS += IMG_png.o
OBJECTS += IMG_pnm.o
OBJECTS += IMG_tga.o
OBJECTS += IMG_tif.o
OBJECTS += IMG_webp.o
OBJECTS += IMG_xcf.o
OBJECTS += IMG_xpm.o
OBJECTS += IMG_xv.o
OBJECTS += IMG_xxx.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)
