BUILD=ldd_admin pdd_admin liblpdd.a

LPDDLIB_OBJS = .obj/CLDDGt02.o .obj/CPDDGt02.o

OBJS_LDD_ADMIN = .obj/ldd_admin.o .obj/CLDDGt02.o .obj/CPDDGt02.o  

OBJS_PDD_ADMIN = .obj/pdd_admin.o .obj/CPDDGt02.o 

#$(patsubst %.cpp, %.o, $(wildcard *.cpp))

CPPFLAGS+=-ggdb \
	-D_FILE_OFFSET_BITS=64 -D_LARGE_FILE \
	-I../../public/utility/ \
	-I../../public/html/ \
	-I$(SOFT)/openssl/include/ \
	-I../../public/linespm/

LDFLAGS+=\
	-L../../public/linespm/ -llinespm \
	-L../../public/html/ -lhtml \
	-L../../public/utility/  -lutility \
	-lpthread -lrt 
	

all:$(BUILD)

.obj/%.o:%.cpp
	mkdir -p .obj
	g++ $(CPPFLAGS) -c  -o $@ $<

	
liblpdd.a:$(LPDDLIB_OBJS)	
	@ar rcs $@ $?
	
ldd_admin:$(OBJS_LDD_ADMIN)
	g++ -o $@ $? $(LDFLAGS)	
	
pdd_admin:$(OBJS_PDD_ADMIN)
	g++ -o $@ $? $(LDFLAGS)	
	
clean:
	rm $(BUILD) .obj/*.o


