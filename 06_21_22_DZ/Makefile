CFLAGS = -g3 -fno-stack-protector -no-pie
MASS = stack
	
all: obj bin $(MASS)

bin:
	mkdir bin
obj:
	mkdir obj

$(MASS): main.o
	gcc $(CFLAGS) -o bin/$(MASS) obj/main.o

main.o: main.c
	gcc -c $(CFLAGS) -o obj/main.o main.c

clean:
	rm -R obj bin

run:
	./bin/$(MASS) < in.txt

.PHONY: clean run