cmake_minimum_required(VERSION 2.8.7)
cmake_policy(VERSION 2.8.7)
project(Physics CXX)

find_package(CGUL 0.1.6 REQUIRED)

include_directories(${CGUL_INCLUDE_DIRS})
add_executable(physics
    src/main.cpp
    src/State.cpp
    src/StateMachine.cpp
    src/StateBoxes.cpp
    src/StateCircles.cpp
    src/Render.cpp
    src/Collision.cpp
    src/AxisAlignedBox.cpp
    src/OrientedBox.cpp
    src/Circle.cpp
)
target_link_libraries(physics ${CGUL_LIBRARIES})
cgul_bake_rpath(physics "$ORIGIN")

if(NOT CGUL_STATIC)
    get_target_property(__CGUL_PATH CGUL IMPORTED_LOCATION)
    get_filename_component(__CGUL_NAME ${__CGUL_PATH} NAME)
    add_custom_target(${__CGUL_NAME} ALL COMMAND cmake -E copy "${__CGUL_PATH}" "${CMAKE_CURRENT_BINARY_DIR}/" VERBATIM)
endif()
