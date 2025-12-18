CFLAGS = -I. -Wno-int-to-pointer-cast -mfpu=neon -lm
CC = gcc

.PHONY: build
build:
	gcc main.c timers_b.c fonctions_ES.c \
		-mfpu=neon -I. -o main -lm -O3
	./main


.PHONY: dot_product
dot_product: dot_product.o baseline.o xmk_dot_product.o timers_b.o
	gcc dot_product.o baseline.o xmk_dot_product.o timers_b.o -lgcc -o dot_product
	./dot_product

clean:
	@rm -f dot_product
	@rm -f main
	@rm -f *.o
