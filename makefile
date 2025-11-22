BINDIR=bin/
SOURCEDIR=src/

build:
	zcc +ti83p -o $(BINDIR)wolfti -create-app $(SOURCEDIR)main.c
keytest:
	zcc +ti83p -o $(BINDIR)keytest -create-app $(SOURCEDIR)keytest.c

all:
	make build
	make keytest
