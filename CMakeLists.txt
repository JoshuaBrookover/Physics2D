cmake_minimum_required(VERSION 2.8.7)
cmake_policy(VERSION 2.8.7)
project(Physics CXX)

find_package(CGUL 0.1.4 REQUIRED)

include_directories(${CGUL_INCLUDE_DIRS})
add_executable(physics
    main.cpp
    State.cpp
    StateMachine.cpp
    TestState.cpp
    Render.cpp
)
target_link_libraries(physics ${CGUL_LIBRARIES})
cgul_bake_rpath(physics "$ORIGIN")
