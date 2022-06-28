CFLAGS = -Wall -g3
SRCS = source/calc_add.c source/calc_sub.c \
	source/calc_mul.c source/calc_div.c
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
	ar rc lib/$(LIB).a $(OBJC)

main.o: main.c
	gcc ${CFLAGS} -c -o obj/main.o main.c
obj/calc_%.o: source/calc_%.c
	gcc ${CFLAGS} -c -o obj/$(@F) source/$(<F)

clean:
	rm -R obj bin lib

print_objc:
	$(info $$var is [${OBJC}])

.PHONY: all clean