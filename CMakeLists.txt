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


if (WIN32)
    set(QT5_PATH  "D:\\Qt5\\5.15.2\\msvc2019_64")
    list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
endif (WIN32)

find_package(Qt5 COMPONENTS Core REQUIRED)

include_directories( "src" )
include_directories( "include" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

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

set(SRC_HEADERS_TEST
	gtest/gtest.cpp
	gtest/gtest_logger.cpp
	gtest/gtest_logger.hpp
    gtest/gtest_configreader.cpp
    gtest/gtest_configreader.hpp
    gtest/gtest_mainlogger.cpp
    gtest/gtest_mainlogger.hpp
)


macro(copy_json jsonname)
	configure_file(${jsonname} ${CMAKE_CONFIGURATION_TYPES}/${jsonname})
endmacro()
MESSAGE(STATUS "utils2 CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES}")
copy_json("gtest/test.json")

add_library(${PROJECT_NAME}_lib STATIC
    ${SRC_LOGGING} ${HEADERS_LOGGING})

target_link_libraries(${PROJECT_NAME}_lib 
processing_module_lib
Qt::Core 
Threads::Threads
)

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

add_executable(${PROJECT_NAME}_test ${SRC_HEADERS_TEST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib gtest gmock)

#gtest_discover_tests(${PROJECT_NAME}_test)