set(TARGET Input)
set(SOURCE_FILES 
        InputComponent.cpp
        GraphicsInputComponent.cpp
)

add_library(${TARGET} "")

target_sources(${TARGET}
        PUBLIC
        ${SOURCE_FILES}
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET} PUBLIC
  Common
  glfw
  imgui
)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Input")
