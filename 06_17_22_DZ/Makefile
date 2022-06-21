CFLAGS = -Wall
PACK = pack
KTLOG = katalog
	
all: obj bin $(KTLOG) $(PACK)

bin:
	mkdir bin
obj:
	mkdir obj

$(KTLOG): main.o katalog.o
	gcc $(CFLAGS) -o bin/$(KTLOG) obj/main.o obj/katalog.o
$(PACK): pack.o
	gcc $(CFLAGS) -o bin/$(PACK) obj/pack.o

pack.o: pack.c
	gcc -c -o obj/pack.o pack.c
main.o: main.c
	gcc -c -o obj/main.o main.c
katalog.o: katalog.c
	gcc -c -o obj/katalog.o katalog.c

clean:
	rm -R obj bin

.PHONY: clean