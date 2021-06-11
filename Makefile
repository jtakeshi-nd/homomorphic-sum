PALISADE_INCLUDES= -I /usr/local/include/palisade/binfhe -I /usr/local/include/palisade/cereal -I /usr/local/include/palisade -I /usr/local/include/palisade/pke -I /usr/local/include/palisade/core
PALISADE_STATIC_LIBS=/usr/local/lib/libPALISADEbinfhe_static.a /usr/local/lib/libPALISADEpke_static.a /usr/local/lib/libPALISADEcore_static.a 
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
	$(CXX) $(CFLAGS) $(PALISADE_INCLUDES) -o $(BINARY)$@ $< $(PALISADE_STATIC_LIBS)

homomorphicSum : $(SRC)/homomorphicSum.cpp
	$(CXX) $(CFLAGS) $(PALISADE_INCLUDES) -o $(BINARY)/$@ $< $(PALISADE_STATIC_LIBS)

decrypt : $(SRC)/decrypt.cpp
	$(CXX) $(CFLAGS) $(PALISADE_INCLUDES) -o $(BINARY)/$@ $< $(PALISADE_STATIC_LIBS)

clean:
	rm -f $(BINARY)/decrypt $(BINARY)/homomorphicSum $(BINARY)/write
	rm -rf graphene container ctexts

