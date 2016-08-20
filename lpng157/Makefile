# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2
CFLAGS += $(SDL_INCLUDE)
CFLAGS += -I../zlib-1.2.5
CPPFLAGS := $(CFLAGS)

TARGET := libpng.a

OBJECTS := 
OBJECTS  += png.o pngerror.o pngget.o
OBJECTS  += pngmem.o pngpread.o pngread.o
OBJECTS  += pngrio.o pngrtran.o pngrutil.o
OBJECTS  += pngset.o pngtrans.o pngwio.o
OBJECTS  += pngwrite.o pngwtran.o pngwutil.o
OBJECTS  += 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)

