
BUILD=libhtml.a

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CPPFLAGS+=-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE

all:$(BUILD)

%.o:%.cpp
	g++ $(CPPFLAGS) -c  -o $@ $<

$(BUILD):$(OBJS)	
	ar rcs $@ $?
	
clean:
	rm $(BUILD) *.o

