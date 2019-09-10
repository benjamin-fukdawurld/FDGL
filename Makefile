LLVM_PATH := ../../llvm
LLVM_BUILD_PATH := $(LLVM_PATH)/build
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin
LLVM_LIB_PATH := $(LLVM_BUILD_PATH)/lib

CC = $(LLVM_BIN_PATH)/clang
CXX = $(LLVM_BIN_PATH)/clang++

WARNINGS := -Wall \
	-Wextra \
	-Wpedantic \
	-Wswitch-enum \
	-Wunreachable-code \
	-Wunreachable-code-aggressive \
	-Wconversion \
	-Wsign-conversion \
	-Wconditional-uninitialized

CFLAGS := -g
CXXFLAGS := -std=c++17 $(CFLAGS) $(WARNINGS)
LDFLAGS :=
DEFINES :=
INCLUDEPATH := -Iinclude/ -I../thirdparty/glad/include -I../thirdparty/glm
LIBPATH :=
LIBS := -lGL -lpthread -ldl -lX11 -lXrandr

PWD := $(shell pwd)
OUTDIR := $(PWD)/../build
LIBDIR := $(OUTDIR)/lib
OBJDIR := $(OUTDIR)/obj

SRCDIR := src
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

.PHONY: clean mrproper builddir

all: libglad.a libFDGL.a

builddir:
	mkdir -p $(OUTDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(OBJDIR)

libFDGL.a: $(OBJFILES)
	ar rcs $(LIBDIR)/libFDGL.a $^

libglad.a: builddir glad.o
	ar rcs $(LIBDIR)/libglad.a $(OBJDIR)/glad.o

glad.o: builddir ../thirdparty/glad/src/glad.c
	$(CXX) $(INCLUDEPATH) -o $(OBJDIR)/glad.o -c ../thirdparty/glad/src/glad.c $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(INCLUDEPATH) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*

mrproper:
	rm -rf $(OUTDIR)