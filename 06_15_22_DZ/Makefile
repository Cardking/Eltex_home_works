CFLAGS = -Wall
GET_BYTE = get_byte_ptr
	
all: obj bin $(GET_BYTE)

bin:
	mkdir bin
obj:
	mkdir obj

$(GET_BYTE): main.o
	gcc $(CFLAGS) -o bin/$(GET_BYTE) obj/main.o

main.o: main.c
	gcc -c -o obj/main.o main.c

clean:
	rm -R obj bin

.PHONY: clean