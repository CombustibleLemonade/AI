# Install script for directory: /home/jan/GitRepository/AI/cmake/Packages/FTGL/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jan/GitRepository/AI/Game/cmake/Packages/FTGL/src/libftgld.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/FTGL/FTTriangleExtractorGlyph.h;/usr/local/include/FTGL/FTTextureGlyph.h;/usr/local/include/FTGL/FTGlyph.h;/usr/local/include/FTGL/FTGLExtrdFont.h;/usr/local/include/FTGL/FTGLPolygonFont.h;/usr/local/include/FTGL/FTBufferFont.h;/usr/local/include/FTGL/FTGLTriangleExtractorFont.h;/usr/local/include/FTGL/FTBuffer.h;/usr/local/include/FTGL/FTGLTextureFont.h;/usr/local/include/FTGL/FTBitmapGlyph.h;/usr/local/include/FTGL/FTOutlineGlyph.h;/usr/local/include/FTGL/FTSimpleLayout.h;/usr/local/include/FTGL/FTFont.h;/usr/local/include/FTGL/FTGLBitmapFont.h;/usr/local/include/FTGL/FTExtrdGlyph.h;/usr/local/include/FTGL/FTBBox.h;/usr/local/include/FTGL/ftgl.h;/usr/local/include/FTGL/FTLayout.h;/usr/local/include/FTGL/FTPoint.h;/usr/local/include/FTGL/FTBufferGlyph.h;/usr/local/include/FTGL/FTPolyGlyph.h;/usr/local/include/FTGL/FTPixmapGlyph.h;/usr/local/include/FTGL/FTGLPixmapFont.h;/usr/local/include/FTGL/FTGLOutlineFont.h")
FILE(INSTALL DESTINATION "/usr/local/include/FTGL" TYPE FILE FILES
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTTriangleExtractorGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTTextureGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLExtrdFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLPolygonFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTBufferFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLTriangleExtractorFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTBuffer.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLTextureFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTBitmapGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTOutlineGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTSimpleLayout.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLBitmapFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTExtrdGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTBBox.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/ftgl.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTLayout.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTPoint.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTBufferGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTPolyGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTPixmapGlyph.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLPixmapFont.h"
    "/home/jan/GitRepository/AI/cmake/Packages/FTGL/src/FTGL/FTGLOutlineFont.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

