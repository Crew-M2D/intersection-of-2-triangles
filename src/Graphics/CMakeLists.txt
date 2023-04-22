set(TARGET Graphics)
set(SOURCE_FILES 
        GraphicsComponent.cpp
        3dParty/imgui_impl_glfw.cpp
        3dParty/imgui_impl_opengl3.cpp
)

add_library(${TARGET} "")

target_sources(${TARGET}
        PUBLIC
        ${SOURCE_FILES}
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)

target_link_libraries(${TARGET} PUBLIC
        fmt::fmt
        glfw
        glad::glad
        imgui::imgui
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Graphics")