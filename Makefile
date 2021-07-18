build:
	gcc main.c -o main
	gcc assembler.c -o assembler

run:
	./main.bin

clean:
	rm assembler main
