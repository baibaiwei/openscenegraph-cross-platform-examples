PROJECT(EX02_TEXTURE_IMAGE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable.
ADD_EXECUTABLE(ex02-texture-image src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex02-texture-image
    osgViewer
    osgDB
    osgGA
    osg
    OpenThreads
)
