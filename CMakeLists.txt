cmake_minimum_required(VERSION 3.0.0)
project(mygame VERSION 0.1.0)

include(CTest)
enable_testing()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${INCLUDE_DIR})
link_directories(${LIB_DIR})

# set(glew_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GL)
# set(glew_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# include_directories(${glew_INCLUDE_DIR})
# link_directories(${glew_LIB_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# add_library(glew SHARED IMPORTED)
# set_property(TARGET glew PROPERTY IMPORTED_LOCATION  ${CMAKE_CURRENT_SOURCE_DIR}/glew32.dll)
# set_property(TARGET glew PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/glew32.lib)


add_executable(mygame main.cpp)


target_link_libraries(mygame  SDL2main SDL2 glew32 opengl32 )
