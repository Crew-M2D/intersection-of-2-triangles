set(TARGET Entrypoint)
set(SOURCE_FILES 
        main.cpp
)

add_executable(${TARGET} "")

target_sources(${TARGET}
    PUBLIC
    ${SOURCE_FILES}
)

# target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
find_package(fmt REQUIRED)

target_link_libraries(${TARGET} PUBLIC
    Common
    Graphics
    Input 
    Math
    fmt::fmt
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Entrypoint")

if(MSVC)
  target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()