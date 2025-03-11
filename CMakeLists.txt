cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(utils2  VERSION 0.0  DESCRIPTION "utils2 Windows/Linux"  LANGUAGES C CXX)

set(TARGET_NAME "utils2")

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_OPTIONS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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
	configure_file(${jsonname} ${CMAKE_BUILD_TYPE}/${jsonname})
endmacro()
MESSAGE(STATUS "utils2 CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
copy_json("gtest/test.json")


add_library(${PROJECT_NAME} SHARED ${SRC_LOGGING} ${HEADERS_LOGGING})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core)
target_compile_definitions(${PROJECT_NAME} PRIVATE UTILS2_SHARED)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

#install(TARGETS ${PROJECT_NAME}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
 #   PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
#install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
#    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")

#add_executable(${PROJECT_NAME}_test ${SRC_HEADERS_TEST})
#target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} gtest gmock Qt::Core)

#gtest_discover_tests(${PROJECT_NAME}_test)

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