CFLAGS = -Wall -g3
SRCS = $(wildcard source/*.c)
OBJC = $(SRCS:source/%.c=obj/%.o)
BINS = $(SRCS:source/%.c=bin/% )
	
all: obj bin lib $(BINS)

bin:
	mkdir bin
obj:
	mkdir obj
lib:
	mkdir lib

bin/%: obj/%.o
	gcc ${CFLAGS} -o $@ $<

obj/%.o: source/%.c
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -R obj bin lib
print_CONSTS:
	$(info $$var is [${SRCS}])
	$(info $$var is [${OBJC}])
	$(info $$var is [${BINS}])

task_%: bin/task_%
	./bin/$@

.PHONY: all clean task_%