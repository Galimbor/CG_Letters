add_executable(pl4 main.cpp)

target_link_libraries(pl4
    LINK_PUBLIC
        glfw
        glad
        ${CMAKE_DL_LIBS}
)
