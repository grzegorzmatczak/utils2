cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(utils2  VERSION 0.0  DESCRIPTION "utils2 Windows/Linux"  LANGUAGES C CXX)

set(DEFAULT_BUILD_TYPE "Release")
#set(CMAKE_BUILD_TYPE "Release")
set(TARGET_NAME "utils2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /O2 /MD" )
endif (WIN32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (WIN32)
	set(QT5_PATH  "D:\\Qt\\5.15.2\\msvc2019_64")
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH}"\\bin\\")
endif (WIN32)

find_package(Qt5 COMPONENTS Core REQUIRED)


include_directories( "src" )
include_directories( "include" )

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL)

enable_testing()

set(SRC_LOGGING
src/logger.cpp
src/mainlogger.cpp)


set(HEADERS_LOGGING
include/logger.hpp
include/mainlogger.hpp)

set(SRC_HEADERS_TEST
	gtest/gtest.cpp
    gtest/gtest_logger.cpp
	gtest/gtest_logger.hpp
	gtest/gtest_mainlogger.cpp
	gtest/gtest_mainlogger.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME}_lib STATIC
	${SRC_LOGGING} ${HEADERS_LOGGING})

add_executable(g_test ${SRC_HEADERS_TEST})

target_link_libraries(${PROJECT_NAME}_lib Qt5::Core Threads::Threads)

target_link_libraries(g_test ${PROJECT_NAME}_lib GTest::GTest gmock)

install(TARGETS ${PROJECT_NAME}_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
	
install(TARGETS ${PROJECT_NAME}_lib EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} ")

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


if (WIN323)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN323)