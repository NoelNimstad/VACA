NAME = VACA
RELEASE = a
VERSION = 0-0

LIBRARIES = -lSDL2 -lSDL2_image

CC = gcc
INCLUDE = -Iinclude -Isource
LIBS = -Llibraries

FROM = source/VACA/*.c test/tilemap.c
TO = build/VACA.app/Contents

ASSETS = test/Resources

O = -O2

all: comp run

comp:
	cp -r $(ASSETS) $(TO)/
	$(CC) $(FROM) -o $(TO)/MacOS/$(NAME)$(RELEASE)$(VERSION) $(INCLUDE) $(LIBS) $(LIBRARIES) $(O)
	codesign --force --deep --sign - build/VACA.app

run:
	cd $(TO) ; ./MacOS/$(NAME)$(RELEASE)$(VERSION)