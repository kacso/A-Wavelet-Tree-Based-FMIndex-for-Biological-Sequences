PROJECT = FMIndex
SOURCE = Main.cpp FMIndex.cpp PrefixSum.cpp WaveletTree.cpp LFTable.cpp KarkkainenSA.cpp 
HEADERS = FMIndex.h PrefixSum.h WaveletTree.h LFTable.h WaveletTreeItem.h Sort.h SuffixArray.h IOcc.h KarkkainenSA.h sais.hxx esa.hxx

CC = g++
CXXFLAGS = -std=c++11 -w
LDFLAGS = 
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
