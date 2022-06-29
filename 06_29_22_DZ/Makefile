CFLAGS = -Wall -g3
SRCS = $(wildcard source/calc_*.c)
OBJC = $(SRCS:source/calc_%.c=obj/calc_%.o)
LIB = libcalc
CALC = calc
	
all: obj bin lib $(LIB) $(CALC)

bin:
	mkdir bin
obj:
	mkdir obj
lib:
	mkdir lib

$(CALC): main.o
	gcc $(CFLAGS) -o bin/$(CALC) obj/main.o -L./lib -lcalc
$(LIB): $(OBJC) 
	gcc -shared -o lib/$(LIB).so $(OBJC)

main.o: main.c
	gcc ${CFLAGS} -c -o obj/main.o main.c
obj/calc_%.o: source/calc_%.c
	gcc ${CFLAGS} -fPIC -c -o obj/$(@F) source/$(<F)

clean:
	rm -R obj bin lib
run:
	LD_LIBRARY_PATH=$$PWD/lib:$$LD_LIBRARY_PATH ./bin/calc

print_SRCS:
	$(info $$var is [${SRCS}])

.PHONY: all clean