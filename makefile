NAME = VACA
RELEASE = a
VERSION = 0-0

LIBRARIES = -lSDL2 -lSDL2_image

CC = gcc
INCLUDE = -Iinclude -Isource
LIBS = -Llibraries

FROM = source/VACA/*.c test/test.c
TO = build

ASSETS = test/assets

O = -O2

all: comp run

comp:
	cp -r $(ASSETS) $(TO)/
	$(CC) $(FROM) -o $(TO)/$(NAME)$(RELEASE)$(VERSION) $(INCLUDE) $(LIBS) $(LIBRARIES) $(O)

run:
	$(TO)/$(NAME)$(RELEASE)$(VERSION)