add_executable(CG_GROUP main.cpp)

target_link_libraries(CG_GROUP
    LINK_PUBLIC
        glfw
        glad
        glm
        ${CMAKE_DL_LIBS}
)
