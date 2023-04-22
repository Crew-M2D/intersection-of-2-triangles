set(TARGET Test)
set(SOURCE_FILES 
    test.cpp
)

add_executable(${TARGET} "")

target_sources(${TARGET}
    PUBLIC
    ${SOURCE_FILES}
)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

target_link_libraries(${TARGET} PUBLIC
    Common
    Graphics
    Input 
    Math
    fmt::fmt
    gtest::gtest
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "tests")

if(MSVC)
  target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()

