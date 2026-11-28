include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
)

FetchContent_MakeAvailable(googletest)

add_executable(translator_tests
    LexicalTests.cpp
    SyntaxTests.cpp
    PostfixTests.cpp
)

target_link_libraries(translator_tests PRIVATE
    translator_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(translator_tests)