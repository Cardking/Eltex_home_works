CFLAGS = -Wall -g3
TEST = bin/fileio
	
all: obj bin $(TEST)

bin:
	mkdir bin
obj:
	mkdir obj
lib:
	mkdir lib

#$(CALC): obj/main.o
#	gcc $(CFLAGS) -o bin/$(CALC) obj/main.o -ldl

$(TEST): obj/main.o
	gcc $(CFLAGS) -o $@ $<

obj/main.o: main.c
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -R obj bin

run:
	./$(TEST)

.PHONY: all clean
.PRECIOUS: obj/main.o