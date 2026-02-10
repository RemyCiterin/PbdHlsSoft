CFLAGS = -I. -Wno-int-to-pointer-cast -mfpu=neon -lm -O3
CC = gcc

.PHONY: build
build:
	gcc main.c timers_b.c fonctions_ES.c xmk_dot_product.c $(CFLAGS)
	./main


.PHONY: dot_product
dot_product: dot_product.o baseline.o xmk_dot_product.o timers_b.o
	gcc dot_product.o baseline.o xmk_dot_product.o timers_b.o -lgcc -o dot_product -O0
	./dot_product

clean:
	@rm -f dot_product
	@rm -f main
	@rm -f *.o
