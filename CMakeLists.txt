# (c) Copyright, Real-Time Innovations, 2020.  All rights reserved.
# RTI grants Licensee a license to use, modify, compile, and create derivative
# works of the software solely for use with RTI Connext DDS. Licensee may
# redistribute copies of the software provided that all such copies are subject
# to this license. The software is provided "as is", with no warranty of any
# type, including any warranty for fitness for any purpose. RTI is under no
# obligation to maintain or support the software. RTI shall not be liable for
# any incidental or consequential damages arising out of the use or inability
# to use the software.

cmake_minimum_required(VERSION 3.14)

project(multi_topic CXX)

set(RTIDDSGEN $ENV{NDDSHOME}/bin/rtiddsgen)
set(TARGET_ARCH x64Linux4gcc7.3.0)

set(IDL_SOURCE 
    ./idl/type1.idl
    ./idl/type2.idl 
    ./idl/type3.idl 
    ./idl/type4.idl 
)

if(NOT EXISTS generated)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ../generated)
endif()
set(IDL_GEN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/generated)

if(NOT EXISTS obj)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ../obj/${TARGET_ARCH}/Release)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ../obj/${TARGET_ARCH}/Debug)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${IDL_GEN_ROOT} 
    $ENV{NDDSHOME}/include
    $ENV{NDDSHOME}/include/ndds
)
link_directories($ENV{NDDSHOME}/lib/${TARGET_ARCH})

add_compile_definitions(RTI_UNIX RTI_LINUX RTI_64BIT RTI_STATIC)
add_compile_options(-m64 -Wall)
set(SYSTEM_LIBS dl m pthread rt)

if(CMAKE_BUILD_TYPE EQUAL Debug)
    add_compile_options(-g -O0)
    add_link_options(-g)
    set(DEBUG_SFX d)
endif()

# this loop does two things:
# 1) generates source files from each idl
# 2) creates a list of those generated files 
foreach(idl ${IDL_SOURCE})
    get_filename_component(filename ${idl} NAME)
    message("${filename}")
    string(REGEX REPLACE "\\.idl" "" basename ${filename})
    set(THIS_PASS_CXX 
            ${IDL_GEN_ROOT}/${basename}.cxx
            ${IDL_GEN_ROOT}/${basename}Plugin.cxx
            ${IDL_GEN_ROOT}/${basename}Support.cxx
    )
    set(THIS PASS_H 
            ${IDL_GEN_ROOT}/${basename}.h
            ${IDL_GEN_ROOT}/${basename}Plugin.h  
            ${IDL_GEN_ROOT}/${basename}Support.h
    )
    execute_process(
            COMMAND ${RTIDDSGEN} -language C++ -namespace -replace -d ${IDL_GEN_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/${idl}
    )                   
    list(APPEND IDL_GEN_CXX ${THIS_PASS_CXX})   
    list(APPEND IDL_GEN_H ${THIS_PASS_H})
endforeach()

add_executable(node_one
    ${CMAKE_CURRENT_SOURCE_DIR}/node_one.cxx
    ${IDL_GEN_CXX} 
    ${IDL_GEN_H}
)
target_link_libraries(node_one 
    libnddscppz${DEBUG_SFX}.a 
    libnddscz${DEBUG_SFX}.a 
    libnddscorez${DEBUG_SFX}.a 
    ${SYSTEM_LIBS}
)
set_target_properties(node_one 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ../obj/${TARGET_ARCH}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ../obj/${TARGET_ARCH}/Release
)

add_executable(node_two
    ${CMAKE_CURRENT_SOURCE_DIR}/node_two.cxx
    ${IDL_GEN_CXX} 
    ${IDL_GEN_H}
)
target_link_libraries(node_two 
    libnddscppz${DEBUG_SFX}.a 
    libnddscz${DEBUG_SFX}.a 
    libnddscorez${DEBUG_SFX}.a 
    ${SYSTEM_LIBS}
)
set_target_properties(node_two 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ../obj/${TARGET_ARCH}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ../obj/${TARGET_ARCH}/Release
)