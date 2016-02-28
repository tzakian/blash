CXX=g++
FLAGS=-std=c++14 -stdlib=libc++ -Wall
LDFLAGS+= -lpthread -lssl -lcrypto

DEPENDS= main.cpp

#blash.cpp

LIBS= blash.cpp

LIBOBJECTS = -L./cuckoofilter/src/hashutil.o -Lblash.o

HEADERS = -I./cuckoofilter/src/cuckoofilter.h -Iblash.hpp

all: make_objs exc
 
make_objs: $(LIBS)
	$(CXX) $(FLAGS) ${LDFLAGS} $(HEADERS) $(LIBOBJECTS) -c $^

exc: $(DEPENDS)
	$(CXX)  $(FLAGS) $(LDFLAGS) $(HEADERS) $(LIBOBJECTS) $(DEPENDS) -o main

clean:
	rm main
