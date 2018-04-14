EXES = $(patsubst %_exe.cpp, %_exe, $(wildcard *_exe.cpp))

BUILD=libbpml.a $(EXES)

OBJS = $(patsubst %.cpp, .obj/%.o, $(wildcard *.cpp))

CPPFLAGS+=-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE -I../utility/ -I../html/ -I../http/ -I../logapi/ 

LD_FLAGS+=-L../utility/ -lutility -L../html/ -lhtml -L../http/ -lhttp -L$(SOFT)/gd/lib -lgd  -lssl -lcrypto  -ldl -lz

all:$(BUILD)

.obj/%.o:%.cpp
	mkdir -p .obj
	g++ $(CPPFLAGS) -c  -o $@ $<



libbpml.a:$(OBJS)	
	ar rcs $@ $?


MyBPML_exe:MyBPML_exe.o libbpml.a
	g++ -o $@ $? $(CPPFLAGS) $(LD_FLAGS)

	
clean:
	rm $(BUILD) $(OBJS)

