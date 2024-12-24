COMPILER := g++
FLAGS_ERROR := -Wall -Wextra -Werror

SOURCE := main.cpp
RESULT := EntityStatsExtractor
OBJS = $(SOURCE:.cpp=.o)
DEPENDACIES := $(SOURCE:.cpp=.d)

# execute rules even if files exist
.PHONY: all clean

all: linking

linking: $(OBJS)
	$(COMPILER) $(FLAGS_ERROR) $^ -o $(RESULT)

%.o: %.cpp
	$(COMPILER) $(FLAGS_ERROR) -MMD -MP -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPENDACIES) $(RESULT)
