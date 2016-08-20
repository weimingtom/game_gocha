# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2
CFLAGS += 
CFLAGS += $(SDL_INCLUDE)
CFLAGS += -I../freetype-2.3.12/include
CPPFLAGS := $(CFLAGS)

TARGET := libSDL_ttf.a

OBJECTS :=
OBJECTS += SDL_ttf.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)
