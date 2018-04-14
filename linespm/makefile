BUILD=liblinespm.a

OBJS = $(patsubst %.cpp, .obj/%.o, $(wildcard *.cpp))

CPPFLAGS+=-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE -O3


LIBPATH=-L../  -L../utility/  -L../../SOFT/openssl/lib/

INCPATH=-I../ -I../utility/  -I../../../SOFT/openssl/include/

LIBS=-lutility


all:$(BUILD)

.obj/%.o:%.cpp
	mkdir -p .obj
	g++ $(CPPFLAGS) $(INCPATH) -c  -o $@ $<

$(BUILD):$(OBJS)	
	ar rcs $@ $?
	
clean:
	rm -rf $(OBJS) $(BUILD)

echo:
	echo $(OBJS)
