# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -std=c++17

# Define the linker flags for OpenSSL libraries
LDFLAGS = -lssl -lcrypto

# Define the source file
SRCS = main.cpp

# Define the executable name
TARGET = main.out

# The default rule to build the target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Rule to clean up compiled files
clean:
	rm -f $(TARGET)