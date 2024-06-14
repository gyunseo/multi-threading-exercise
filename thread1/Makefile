CC = gcc
TARGET := t1
OUTPUT = $(TARGET).out
CCFLAGS = -Og -Wextra -Werror -Wall
LIBS = -pthread

all: $(OUTPUT)
$(OUTPUT) : $(TARGET).o
	$(CC) $< -o $@ $(LIBS)


$(TARGET).o: $(TARGET).c
	$(CC) $(CCFLAGS) -c $< -o $@ $(LIBS)



.PHONY: clean
clean:
	rm -f $(OUTPUT) $(TARGET).o
