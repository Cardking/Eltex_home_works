CFLAGS = -Wall -g3
SRCS = $(wildcard source/*.c)
OBJC = $(SRCS:source/%.c=obj/%.o)
BIN = bin/pthread
	
all: obj bin lib $(BIN)

bin:
	mkdir bin
obj:
	mkdir obj
lib:
	mkdir lib

$(BIN): obj/main.o
	gcc ${CFLAGS} -o $@ $< -lpthread

obj/%.o: source/%.c
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -R obj bin lib
print_CONSTS:
	$(info $$var is [${SRCS}])
	$(info $$var is [${OBJC}])
	$(info $$var is [${BINS}])

run: $(BIN)
	./$(BIN)

.PHONY: all clean run