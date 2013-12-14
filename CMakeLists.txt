cmake_minimum_required(VERSION 2.8.7)
cmake_policy(VERSION 2.8.7)
project(Physics CXX)

find_package(CGUL 0.1.6 REQUIRED)

include_directories(${CGUL_INCLUDE_DIRS})
add_executable(physics
    src/main.cpp
    src/State.cpp
    src/StateMachine.cpp
    src/TestState.cpp
    src/Render.cpp
    src/Collision.cpp
    src/AxisAlignedBox.cpp
    src/OrientedBox.cpp
    src/Circle.cpp
)
target_link_libraries(physics ${CGUL_LIBRARIES})
cgul_bake_rpath(physics "$ORIGIN")
