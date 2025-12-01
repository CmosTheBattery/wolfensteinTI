BINDIR=bin/
SOURCEDIR=src/

build:
	mkdir -p $(BINDIR)
	make main
	make keytest

main:
	zcc +ti83p -o $(BINDIR)wolfti -create-app $(SOURCEDIR)main.c
keytest:
	zcc +ti83p -o $(BINDIR)keytest -create-app $(SOURCEDIR)keytest.c

clean:
	rm -rf $(BINDIR)
