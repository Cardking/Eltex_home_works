CFLAGS = -Wall
MASS = massive
GET_BYTE = get_byte
	
all: obj bin $(MASS) $(GET_BYTE)

bin:
	mkdir bin
obj:
	mkdir obj

$(MASS): main.o
	gcc $(CFLAGS) -o bin/$(MASS) obj/main.o
$(GET_BYTE): get_byte.o
	gcc $(CFLAGS) -o bin/$(GET_BYTE) obj/get_byte.o

main.o: main.c
	gcc -c -o obj/main.o main.c
get_byte.o: get_byte.c
	gcc -c -o obj/get_byte.o get_byte.c

clean:
	rm -R obj bin

.PHONY: clean