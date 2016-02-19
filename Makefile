CXX=g++
FLAGS=-std=c++11 -stdlib=libc++
LDFLAGS+= -Wall -lpthread -lssl -lcrypto

DEPENDS= main.cpp \
				 blash.cpp

LIBOBJECTS = ./cuckoofilter/src/hashutil.o

HEADERS = -I./cuckoofilter/src/cuckoofilter.h -Iblash.hpp

all: $(DEPENDS)
	$(CXX)  $(FLAGS) $(LDFLAGS) $(HEADERS) $(LIBOBJECTS) $(DEPENDS) -o main

clean:
	rm main
