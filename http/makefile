
BUILD=libhttp.a

OBJS = $(patsubst %.cpp, .obj/%.o, $(wildcard *.cpp))

CPPFLAGS+=-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE -I../utility/  -I../html/ -I$(SOFT)/openssl/include/

all:$(BUILD)

.obj/%.o:%.cpp
	mkdir -p .obj
	g++ $(CPPFLAGS) -c  -o $@ $<

$(BUILD):$(OBJS)	
	ar rcs $@ $?
	
clean:
	rm $(BUILD) $(OBJS)

