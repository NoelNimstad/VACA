NAME = VACA
RELEASE = a
VERSION = 0-0

LIBRARIES = -lSDL2 -lSDL2_image

CC = gcc
INCLUDE = -Iinclude
LIBS = -Llibraries

FROM = source
TO = build

O = 

all: comp run

comp:
	$(CC) $(FROM)/*.c -o $(TO)/$(NAME)$(RELEASE)$(VERSION) $(INCLUDE) $(LIBS) $(LIBRARIES) $(O)

run:
	$(TO)/$(NAME)$(RELEASE)$(VERSION)