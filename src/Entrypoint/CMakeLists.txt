set(TARGET Entrypoint)
set(SOURCE_FILES 
        main.cpp
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
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Entrypoint")

if(MSVC)
  target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()
