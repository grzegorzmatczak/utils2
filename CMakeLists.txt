cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(utils2  VERSION 0.0  DESCRIPTION "utils2 Windows/Linux"  LANGUAGES C CXX)

set(TARGET_NAME "utils2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")


if (WIN32)
    set(QT5_PATH  "D:\\Qt5\\5.15.2\\msvc2019_64")
    list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
endif (WIN32)

find_package(Qt5 COMPONENTS Core REQUIRED)


include_directories( "src" )
include_directories( "include" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL)

set(SRC_LOGGING
src/logger.cpp
src/mainlogger.cpp
src/mainlogger.cpp
src/configreader.cpp
)


set(HEADERS_LOGGING
include/logger.hpp
include/mainlogger.hpp
include/configreader.hpp
)
include(GNUInstallDirs)

add_library(${PROJECT_NAME}_lib STATIC
    ${SRC_LOGGING} ${HEADERS_LOGGING})


target_link_libraries(${PROJECT_NAME}_lib Qt::Core Qt::Widgets Threads::Threads)

install(TARGETS ${PROJECT_NAME}_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
install(TARGETS ${PROJECT_NAME}_lib EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
