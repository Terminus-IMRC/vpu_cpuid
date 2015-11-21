all: main

LOADLIBES := -lmailbox -lvc4vec

RM ?= rm -f

main: main.o

.PHONY: clean
clean:
	$(RM) main.o
	$(RM) main
