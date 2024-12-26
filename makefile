COMPILER := g++
LOOK_HERE_TOO := -L/usr/local/lib -I/usr/local/include
FLAGS_ERROR := -Wall -Wextra -Werror

SOURCE := main.cpp 
RESULT := EntityStatsExtractor
OBJS = $(SOURCE:.cpp=.o)
DEPENDACIES := $(SOURCE:.cpp=.d)

# execute rules even if files exist
.PHONY: all clean

all: linking

linking: $(OBJS)
	$(COMPILER) $(FLAGS_ERROR) $(LOOK_HERE_TOO) $^ -o $(RESULT) -lEntityDataExtractor -ljsoncpp

%.o: %.cpp
	$(COMPILER) $(FLAGS_ERROR) $(LOOK_HERE_TOO) -MMD -MP -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPENDACIES) $(RESULT)
