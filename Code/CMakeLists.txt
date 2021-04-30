
cmake_minimum_required(VERSION 3.16)

project(shoot_training)
add_executable(shoot_training main.cpp func.cpp func.hpp hands.cpp hands.hpp  rifle.cpp rifle.hpp image.cpp image.hpp) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(shoot_training ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )