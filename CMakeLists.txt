cmake_minimum_required(VERSION 3.10)
project(opengl-attitude-visualisation)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories ("src/")
include_directories ("src/gl-renderables")
include_directories ("src/gl-renderer")

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory (src/gl-renderables) 
add_subdirectory (src/gl-renderer) 

SET(SERIAL_SRC
  src/AsyncSerial.cpp
  src/BufferedAsyncSerial.cpp
)

add_executable (main main.cpp ${SERIAL_SRC})

link_libraries(${GLEW_LIBRARIES})

set(BOOST_LIBS date_time system)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
target_link_libraries(main ${Boost_LIBRARIES})
find_package(Threads REQUIRED)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries ( 
  main 
  gl-renderables 
  gl-renderer 
  GLEW 
  OpenGL::OpenGL 
  pthread 
  boost_system
  ${GLFW_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES})


# 
#-I"/home/mc18g13/eclipse-workspace/OpenGL-Abstraction/src/gl-renderables" 
#-IGL -I"/home/mc18g13/eclipse-workspace/OpenGL-Abstraction/src/gl-renderer" 
#-I"/home/mc18g13/eclipse-workspace/OpenGL-Abstraction/src" -IGLU -Iglfw -O0 -g3 -Wall -c -fmessage-length=0