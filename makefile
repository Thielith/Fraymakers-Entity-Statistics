COMPILER := g++
FLAGS_ERROR := -Wall -Wextra -Werror

SOURCE := main.cpp
RESULT := EntityStatsExtractor
OBJS = $(SOURCE:.cpp=.o)
DEPENDACIES := $(SOURCE:.cpp=.d)

# execute rules even if files exist
.PHONY: all clean

all: linking

clean:
	$(RM) $(OBJS) $(DEPENDACIES) $(RESULT) linking

linking: $(OBJS)
	$(COMPILER) $(FLAGS_ERROR) $(FLAGS) $^ -o $(RESULT)

-include $(DEPENDACIES)

# Compile .cpp files into .o files
%.o: %.cpp
	$(COMPILER) $(FLAGS) -MMD -MP -c $< -o $@

# Run result
run: $(RESULT)
	./$(RESULT)


