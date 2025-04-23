exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic
asm_flags = -f elf64
asm_exec = test.o

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

asm:
	nasm test.out $(asm_flags)
	ld test.o -o b.out
	rm test.o
	
cl:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
	-rm examples/*.o
	-rm examples/*.out

