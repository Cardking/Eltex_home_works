CFLAGS = -Wall -g3
SRCS = $(wildcard source/calc_*.c)
OBJC = $(SRCS:source/calc_%.c=obj/calc_%.o)
LIBS = $(SRCS:source/calc_%.c=lib/calc_%.so)
CALC = bin/calc
TEST = bin/test
	
all: obj bin lib lib/dl_func.so $(LIBS) $(CALC) $(TEST)

bin:
	mkdir bin
obj:
	mkdir obj
lib:
	mkdir lib

#$(CALC): obj/main.o
#	gcc $(CFLAGS) -o bin/$(CALC) obj/main.o -ldl
$(CALC): obj/main.o
	gcc $(CFLAGS) -o $@ $< -ldl
$(TEST): obj/test.o
	gcc $(CFLAGS) -o $@ $< -ldl


lib/calc_%.so: obj/calc_%.o
	gcc -shared -o $@ $<
lib/dl_func.so: obj/dl_func.o 
	gcc -shared -o lib/dl_func.so obj/dl_func.o

obj/calc_%.o: source/calc_%.c
	gcc ${CFLAGS} -fPIC -c -o obj/$(@F) source/$(<F)
obj/dl_func.o: source/dl_func.c
	gcc -fPIC -c -o obj/dl_func.o source/dl_func.c
obj/main.o: main.c
	gcc ${CFLAGS} -c -o $@ $<
obj/test.o: test.c
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -R obj bin lib

run:
	./bin/calc
run_test:
	./bin/test

print_SRCS:
	$(info $$var is [${SRCS}])

.PHONY: all clean
.PRECIOUS: obj/calc_%.o