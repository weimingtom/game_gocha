# Makefile to build the SDL library
include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2
CFLAGS += $(SDL_INCLUDE)
CPPFLAGS := $(CFLAGS)

TARGET := libz.a

OBJECTS := 
OBJECTS += adler32.o compress.o crc32.o
OBJECTS += deflate.o gzclose.o gzlib.o
OBJECTS += gzread.o gzwrite.o infback.o
OBJECTS += inffast.o inflate.o inftrees.o
OBJECTS += trees.o uncompr.o zutil.o
OBJECTS += 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)
