# sources
OBJS = main.o
SRCS = $(subst .o,.c, $(OBJS)))

# Executable name
TARGET=i2cscan

# GCC compiling & linking flags
CFLAGS=-g -std=gnu99 -Wall -Werror

# Additional libraries which needs to be dynamically linked to the executable
LIBS=

# Main GCC executable (used for compiling and linking)
CROSS_COMPILE=arm-linux-gnueabi-
CC=$(CROSS_COMPILE)gcc

# Main Makefile target 'all' 
all: $(TARGET)

%.o: %.c version.h
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)

# Clean target - when called it cleans all object files and executables.
clean:
	rm -f $(TARGET) *.o
