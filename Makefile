CXX=g++
FLAGS=-std=c++14 -stdlib=libc++ -Wall
LDFLAGS+= -lpthread -lssl -lcrypto

DEPENDS= main.cpp

LIBOBJECTS = ./cuckoofilter/src/hashutil.o

HEADERS = -I./cuckoofilter/src/cuckoofilter.h 

#-Iblash.hpp

all: exc

exc: $(DEPENDS)
	$(CXX)  $(FLAGS) $(LDFLAGS) $(LIBOBJECTS) $(HEADERS) $(DEPENDS) -o main

clean:
	rm main
