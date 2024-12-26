cmake_minimum_required(VERSION 3.31.3)

project(Fraymakers-Entity-Statistics)

# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

# add_subdirectory(/usr/local/include/fraymakers-entity-data-extractor)

add_executable(EntityStatsExtractor main.cpp)

target_link_libraries(EntityStatsExtractor PUBLIC EntityDataExtractor)
target_include_directories(EntityStatsExtractor PUBLIC 
							"${PROJECT_BINARY_DIR}"
							"/usr/local/include"
)

