# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2 
CFLAGS += $(SDL_INCLUDE) 
CFLAGS += -I../lua5.1/include
CFLAGS += -I../SDL_image-1.2.12
CFLAGS += -I../lpng157
CFLAGS += -I../zlib-1.2.5
CFLAGS += -I../SDL_ttf-2.0.9
CFLAGS += -I../freetype-2.3.12
CFLAGS += -I../tolua++-1.0.92/include
CPPFLAGS := $(CFLAGS)

LDFLAGS :=
LDFLAGS += $(SDLLIB)
LDFLAGS += ../SDL_ttf-2.0.9/libSDL_ttf.a
LDFLAGS += ../freetype-2.3.12/libfreetype.a
LDFLAGS += ../SDL_image-1.2.12/libSDL_image.a
LDFLAGS += ../lpng157/libpng.a
LDFLAGS += ../zlib-1.2.5/libz.a
LDFLAGS += ../tolua++-1.0.92/libtolua++.a
LDFLAGS += ../lua5.1/src/liblua5.1.a

LDFLAGS += -lglaux -lglu32 -lopengl32 -lm -lws2_32 -luser32 -lgdi32 -lwinmm -lmsimg32 -lstdc++
 
TARGET := libgocha.a

OBJECTS := 
OBJECTS += Collision.o GameCommon.o LuaHelper.o
OBJECTS += SpriteNode.o stdafx.o

OBJECTS += tolua_bind/luafunc_glue.o

OBJS_BIN := main.o
BIN := game_gocha.exe

all: $(TARGET) $(BIN)

$(BIN): $(OBJS_BIN) $(TARGET)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(OBJS_BIN) $(BIN)

cleanlibs:
	make -C ../freetype-2.3.12 clean
	make -C ../zlib-1.2.5 clean
	make -C ../lpng157 clean
	make -C ../lua5.1 clean
	make -C ../SDL-1.2.13 clean
	make -C ../SDL_image-1.2.12 clean
	make -C ../SDL_ttf-2.0.9 clean
	make -C ../tolua++-1.0.92 clean
	
alllibs:
	make -C ../freetype-2.3.12 all
	make -C ../zlib-1.2.5 all
	make -C ../lpng157 all
	make -C ../lua5.1 all
	make -C ../SDL-1.2.13 all
	make -C ../SDL_image-1.2.12 all
	make -C ../SDL_ttf-2.0.9 all
	make -C ../tolua++-1.0.92 all
