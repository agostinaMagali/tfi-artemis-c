CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -O2
LDLIBS  = -lm
OBJS    = main.o artemis.o validaciones.o
TARGET  = artemis_tli

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o: main.c artemis.h validaciones.h
artemis.o: artemis.c artemis.h validaciones.h
validaciones.o: validaciones.c validaciones.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
