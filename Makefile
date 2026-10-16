# Makefile de la pràctica «GitHub Actions: compilar un programa en C»
#
#   make         compila el programa
#   make test    compila (si cal) i executa les proves de fum
#   make clean   esborra el que s'ha generat

# (make ja defineix CC=cc per defecte; per això fem servir "=" i no "?=".
#  Es pot canviar des de fora: make CC=clang)
CC     = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2
PROG   := estadistiques

.PHONY: all test clean

all: $(PROG)

$(PROG): $(PROG).c
	gcc $(CFLAGS) -o $@ $<

test: $(PROG)
	@echo "Prova 1: arguments"
	./$(PROG) 4 8 6 | grep -q "Mitjana:   6.00"
	@echo "Prova 2: entrada estandard"
	echo "10 20 30 40" | ./$(PROG) | grep -q "Maxim:     40.00"
	@echo "Prova 3: valor no numeric (ha de tornar codi 2)"
	./$(PROG) 4 hola 6; test $$? -eq 2
	@echo "Totes les proves han passat."

clean:
	rm -f $(PROG)
