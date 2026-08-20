CXX = g++
CXXFLAGS = -O3 -I src/Data -I src/Solucao -I utils

TARGET = a

SOURCES = \
	src/Solucao/main.cpp \
	src/Solucao/iterated_local_search.cpp \
	src/Solucao/solucao.cpp \
	src/Data/Data.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)