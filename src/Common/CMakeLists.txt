set(TARGET Common)
set(SOURCE_FILES 
        Application.cpp
)

add_library(${TARGET} "")

target_sources(${TARGET}
        PUBLIC
        ${SOURCE_FILES}
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET} PUBLIC
        glfw
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Common")
