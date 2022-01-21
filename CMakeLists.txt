cmake_minimum_required(VERSION 3.0.0)
project(imgui_test VERSION 0.1.0)

set(CXX_STANDARD 11)

file(GLOB SOURCE ${CMAKE_SOURCE_DIR}/source/*.cpp
                 ${CMAKE_SOURCE_DIR}/source/utils/*.cpp)

file(GLOB IMGUI_SOURCE ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/*.cpp
                       ${CMAKE_SOURCE_DIR}/3rd/imgui/*.cpp)

file(GLOB GLAD_SOURCE ${CMAKE_SOURCE_DIR}/3rd/glad/src/glad.c)

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/3rd/imgui
                    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends
                    ${CMAKE_SOURCE_DIR}/3rd/glfw
                    ${CMAKE_SOURCE_DIR}/3rd/glad/include)

link_directories(${CMAKE_SOURCE_DIR}/3rd/glfw/lib)

add_executable(imgui_test ${SOURCE} ${IMGUI_SOURCE} ${GLAD_SOURCE})
target_link_libraries(imgui_test X11 glfw3 GL dl pthread)
