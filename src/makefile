PROJECT = FMIndex
SOURCE = Main.cpp FMIndex.cpp PrefixSum.cpp WaveletTree.cpp LFTable.cpp CompressedSuffixArray.cpp HeapSort.cpp WaveletHeapSort.cpp
HEADERS = FMIndex.h PrefixSum.h WaveletTree.h CompressedSuffixArray.h HeapSort.h LFTable.h WaveletTreeItem.h Sort.h SuffixArray.h IOcc.h WaveletHeapSort.h

CC = g++
CXXFLAGS = -std=c++11
LDFLAGS = 
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
