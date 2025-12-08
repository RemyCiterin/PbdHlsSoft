
.PHONY: build
build:
	gcc main.c timers_b.c fonctions_ES.c \
		-mfpu=neon -I. -o main -lm -O3
	./main

clean:
	@rm -f main
