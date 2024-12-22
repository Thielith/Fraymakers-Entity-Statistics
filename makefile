COMPILER := g++
FLAGS := -ljsoncpp

SOURCE := program.cpp
RESULT := program
OBJS = $(SOURCE:.cpp=.o)
DEPENDACIES := $(SOURCE:.cpp=.d)

# execute rules even if files exist
.PHONY: all clean

all: linking

clean:
	$(RM) $(OBJS) $(DEPENDACIES) linking

linking: $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $(RESULT)

-include $(DEPENDACIES)

# Compile .cpp files into .o files
%.o: %.cpp
	$(COMPILER) $(FLAGS) -MMD -MP -c $< -o $@

# Run result
run: $(RESULT)
	./$(RESULT)

windows:
	$(eval COMPILER=x86_64-w64-mingw32-gcc)


