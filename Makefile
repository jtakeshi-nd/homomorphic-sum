PALISADE_INCLUDES= -I /usr/local/include/palisade/binfhe -I /usr/local/include/palisade/cereal -I /usr/local/include/palisade/pke -I /usr/local/include/palisade/core -I /usr/local/include/palisade
PALISADE_STATIC_LIBS=/usr/local/lib/libPALISADEbinfhe_static.a /usr/local/lib/libPALISADEpke_static.a /usr/local/lib/libPALISADEcore_static.a 
PALISADE_DYNAMIC_LIBS_LOCATION=/usr/local/lib
PALISADE_DYNAMIC_LIBS= -l PALISADEbinfhe -l PALISADEcore -l PALISADEpke 
CXX=g++
CFLAGS= -std=c++14 -O3
SRC=src
INCLUDE=include
BINARY=bin


all: initialize homomorphicSum decrypt write graphene

initialize:
	mkdir -p ctexts container

graphene : homomorphicSum decrypt
	mkdir -p graphene/container graphene/ctexts
	cp bin/* graphene/

write : $(SRC)/write.cpp
	$(CXX) $(PALISADE_INCLUDES) -o $(BINARY)/$@ $< $(PALISADE_STATIC_LIBS) -L $(PALISADE_DYNAMIC_LIBS_LOCATION) $(PALISADE_DYNAMIC_LIBS) -Wl,-rpath=$(PALISADE_DYNAMIC_LIBS_LOCATION) -pthread -fopenmp -O3

homomorphicSum : $(SRC)/homomorphicSum.cpp
	$(CXX) $(PALISADE_INCLUDES) -o $(BINARY)/$@ $< $(PALISADE_STATIC_LIBS) -L $(PALISADE_DYNAMIC_LIBS_LOCATION) $(PALISADE_DYNAMIC_LIBS) -Wl,-rpath=$(PALISADE_DYNAMIC_LIBS_LOCATION) -pthread -fopenmp -O3
decrypt : $(SRC)/decrypt.cpp
	$(CXX) $(PALISADE_INCLUDES) -o $(BINARY)/$@ $< $(PALISADE_STATIC_LIBS) -L $(PALISADE_DYNAMIC_LIBS_LOCATION) $(PALISADE_DYNAMIC_LIBS) -Wl,-rpath=$(PALISADE_DYNAMIC_LIBS_LOCATION) -pthread -fopenmp -O3

clean:
	rm -f $(BINARY)/decrypt $(BINARY)/homomorphicSum $(BINARY)/write
	rm -rf graphene container ctexts

