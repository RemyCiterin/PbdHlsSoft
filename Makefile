
.PHONY: build
build:
	gcc main.c timers_b.c fonctions_ES.c \
		-mfpu=neon -I. -o main -lm -O3
	./main

.PHONY: dot_product
dot_product:
	gcc dot_product.c xmk_dot_product.c -I. -o dot_product
	./dot_product

clean:
	@rm -f main
