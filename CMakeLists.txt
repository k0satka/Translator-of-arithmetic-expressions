cmake_minimum_required(VERSION 3.20)

project(ArithmeticTranslator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(translator_core STATIC src/LexicalAnalyzer.cpp src/SyntaxAnalyzer.cpp src/PostfixConverter.cpp src/Evaluator.cpp)

target_include_directories(translator_core PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(translator_cli src/main.cpp)

target_link_libraries(translator_cli PRIVATE translator_core)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()