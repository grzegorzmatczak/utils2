cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(utils2 
    VERSION 0.0.1
    DESCRIPTION "utils2" 
    LANGUAGES C CXX
)
set(TARGET_NAME "utils2")

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_OPTIONS}")
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

include_directories( "src" )
include_directories( "include" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC
    src/logger.cpp
    src/mainlogger.cpp
    src/mainlogger.cpp
    src/configreader.cpp
)

set(HEADERS
    include/logger.hpp
    include/mainlogger.hpp
    include/configreader.hpp
    include/utils2_global.h
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
	configure_file(${jsonname} ${CMAKE_BUILD_TYPE}/${jsonname})
endmacro()
MESSAGE(STATUS "utils2 CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
copy_json("gtest/test.json")


add_library(${PROJECT_NAME} SHARED ${SRC} ${HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core)
target_compile_definitions(${PROJECT_NAME} PRIVATE UTILS2_SHARED_ON)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")

#add_executable(${PROJECT_NAME}_test ${SRC_HEADERS_TEST})
#target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} GTest::gtest Qt::Core)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    CACHE PATH "Location of header files" )
set(SYSCONFIG_INSTALL_DIR ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME}
    CACHE PATH "Location of configuration files" )

install( 
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

install(
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  #NAMESPACE utils2::
  FILE ${PROJECT_NAME}Targets.cmake # Not sure if this is still needed
  )

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMajorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} )
   
if (WIN32)
    get_target_property(QMAKE_EXE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)
    message(STATUS "QT_BIN_DIR:" ${QT_BIN_DIR})
    find_program(WINDEPLOYQT_ENV_SETUP qtenv2.bat HINTS "${QT_BIN_DIR}")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
endif(WIN32)

if (WIN32_temp)
    set(PREFIX_BUILD_TYPE "")
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(PREFIX_BUILD_TYPE "d")
    endif()
    message(STATUS "OPENCV_VERSION_WINDOWS:" ${OPENCV_VERSION_WINDOWS})
    message(STATUS "CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})
    message(STATUS "PREFIX_BUILD_TYPE:" ${PREFIX_BUILD_TYPE})
    message(STATUS "CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
    
    MESSAGE(STATUS "utils2_DIR ${utils2_DIR}")
    add_custom_command ( TARGET ${PROJECT_NAME}_test
        ##COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${utils2_DIR}utils2.dll                              ${utils2_DIR}

        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT_BIN_DIR}/Qt5Test${PREFIX_BUILD_TYPE}.dll        ${utils2_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT_BIN_DIR}/Qt5Gui${PREFIX_BUILD_TYPE}.dll         ${utils2_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT_BIN_DIR}/Qt5Multimedia${PREFIX_BUILD_TYPE}.dll  ${utils2_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT_BIN_DIR}/Qt5Network${PREFIX_BUILD_TYPE}.dll     ${utils2_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT_BIN_DIR}/Qt5Core${PREFIX_BUILD_TYPE}.dll        ${utils2_DIR}
    )
endif(WIN32_temp)