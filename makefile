CC := g++
CFLAGS := -g
TARGET := edit
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))

all:$(TARGET)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $<

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) *.o
