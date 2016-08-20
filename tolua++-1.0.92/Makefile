# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2
CFLAGS += $(SDL_INCLUDE)
CFLAGS += -I../lua5.1/include
CFLAGS += -I./include
CPPFLAGS := $(CFLAGS)

TARGET := libtolua++.a

OBJECTS := 
OBJECTS += src/lib/tolua_event.o
OBJECTS += src/lib/tolua_is.o
OBJECTS += src/lib/tolua_map.o
OBJECTS += src/lib/tolua_push.o
OBJECTS += src/lib/tolua_to.o


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)
