project(expect)
cmake_minimum_required(VERSION 3.5)

#set( CMAKE_C_COMPILER   "gcc-5" )
#set( CMAKE_CXX_COMPILER "g++-5" )

set (CMAKE_C_STANDARD   11)
set (CMAKE_CXX_STANDARD 14)

#add_compile_options(-c)

if (MSVS)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wfloat-equal -Wswitch-default -Wuninitialized -Wunreachable-code -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override)
endif()

#Dr.Memory:              on x64 require g++-multilib
#add_compile_options(-m32 -g -fno-inline -fno-omit-frame-pointer)

if ( ( ${GPROF} ) AND
     ( CMAKE_BUILD_TYPE STREQUAL "DEBUG" ) )
    add_compile_options(-pg)
endif()

file(GLOB_RECURSE HEADER_FILES include *.h*)

aux_source_directory(. SRC_LIST)

# find apr lib
#message(STATUS "looking for apr library.")
#find_path(APR_INCLUDE apr_version.h
#           /usr/include/apr-1.0
## other dirs to search
#)
#include_directories(${APR_INCLUDE})
#message(STATUS "apr inclues ${APR_INCLUDE}")
#
#find_library(APR_LIBRARIES apr-1)
#message(STATUS "apr link with ${APR_LIBRARIES}")

# find xml2 by modules
#include(FindLibXml2)
#include_directories(${LIBXML2_INCLUDE_DIR})
#message(STATUS "xml2 inclues ${LIBXML2_INCLUDE_DIR}")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_FILES})

#message(STATUS "xml2 link with ${LIBXML2_LIBRARIES}")
#target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES})
