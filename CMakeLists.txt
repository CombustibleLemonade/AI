cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(HW_OPENGL)


#Extending the module database
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# Find GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

#########################################################
# Find GLFW
#########################################################
add_subdirectory(cmake/Packages/glfw-3.0.4)
include_directories(cmake/Packages/glfw-3.0.4/include)

#########################################################
# Find FreeType
#########################################################
add_subdirectory(cmake/Packages/freetype-2.5.3)
include_directories(cmake/Packages/freetype-2.5.3/include)

#########################################################
# Find FTGL
#########################################################
add_subdirectory(cmake/Packages/FTGL)
include_directories(cmake/Packages/FTGL/src)

#########################################################
# Find DevIL
#########################################################
find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIRS})
link_directories(${IL_LIBRARIES})
link_directories(${ILU_LIBRARIES})
link_directories(${ILUT_LIBRARIES})

#########################################################
# Include Files
#########################################################
SET(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${CMAKE_SOURCE_DIR}/Common)
add_executable(plotTwist
        Main/Main.cpp
        Common/LoadText.cpp
        Common/Display.cpp
        Common/Control.cpp
        Common/Blocks.cpp)

########################################################
# Linking & stuff
#########################################################

  # create the program "test"
target_link_libraries(plotTwist glfw
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${GLEW_LIBRARY}
    ${IL_LIBRARIES}
    ${ILU_LIBRARIES}
    ${ILUT_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
)
