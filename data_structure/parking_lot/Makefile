CXX = g++
CXXFLAGS = -std=c++17
TARGET = test
SRCS = main.cpp stack.cpp queue.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	printf "A 101\nA 102\nA 103\nA 104\nD 102\nD 101\nD 103\nD 104\nQ\n" | ./$(TARGET)

clean:
	rm -f $(TARGET)
