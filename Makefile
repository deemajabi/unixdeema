CXX = mpic++
CXXFLAGS = -O2
TARGET_SERIAL = dna_Kmers_serial
TARGET_PARALLEL = dna_Kmers_parallel
SRC_SERIAL = dna_Kmers_serial.cpp
SRC_PARALLEL = dna_Kmers_parallel.cpp
OBJ_SERIAL = $(SRC_SERIAL:.cpp=.o)
OBJ_PARALLEL = $(SRC_PARALLEL:.cpp=.o)

all: $(TARGET_SERIAL) $(TARGET_PARALLEL)

$(TARGET_SERIAL): $(OBJ_SERIAL)
	$(CXX) $(OBJ_SERIAL) -o $(TARGET_SERIAL)

$(TARGET_PARALLEL): $(OBJ_PARALLEL)
	$(CXX) $(OBJ_PARALLEL) -o $(TARGET_PARALLEL)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SERIAL) $(TARGET_SERIAL) $(OBJ_PARALLEL) $(TARGET_PARALLEL)

.PHONY: all clean
