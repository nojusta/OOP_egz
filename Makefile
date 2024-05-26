# Kintamieji
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Failai
SRC = main.cpp functions.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Pagrindinis target
all: $(EXEC)

# Linkinimas
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Kompiliavimas
%.o: %.cpp functions.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Išvalymas
clean:
	rm -f $(OBJ) $(EXEC)