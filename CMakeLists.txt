cmake_minimum_required(VERSION 3.20)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(nlohmann.json)

include_directories(include)

add_executable(search_engine
        main.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
)

target_link_libraries(search_engine PRIVATE
        nlohmann_json::nlohmann_json)
