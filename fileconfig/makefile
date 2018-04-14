
BUILD=libfileconfig.a

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))


INC+=-I../utility -I../html 

CPPFLAGS+=-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE  $(INC)

all:$(BUILD)

%.o:%.cpp
	g++ $(CPPFLAGS) -c  -o $@ $<

$(BUILD):$(OBJS)	
	@ar rcs $@ $?
	
clean:
	rm $(BUILD) *.o

