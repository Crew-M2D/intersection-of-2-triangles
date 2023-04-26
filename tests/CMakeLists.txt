set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TARGET Test)
set(SOURCE_FILES 
    test.cpp
)

add_executable(${TARGET} "")

target_sources(${TARGET}
    PUBLIC
    ${SOURCE_FILES}
)

target_link_libraries(${TARGET} PUBLIC
    Common
    Graphics
    Input 
    Math
    gtest_main
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "tests")

if(MSVC)
  target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()

include(GoogleTest)
gtest_discover_tests(${TARGET})

