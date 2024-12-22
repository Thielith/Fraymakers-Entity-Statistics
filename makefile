COMPILER = g++
FLAGS = -ljsoncpp

SOURCE = program.cpp
RESULT = program

OBJS = $(SOURCE:.cpp=.o)


all: $(RESULT) run

# Link object files into the target executable
$(RESULT): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(RESULT) $(OBJS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

# Run result
run: $(RESULT)
	./$(RESULT)

clean:
	del $(RESULT) $(OBJS)
