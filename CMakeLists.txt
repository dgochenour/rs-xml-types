cmake_minimum_required(VERSION 3.1)

project(rs-xml-types CXX)

#set(TARGET_ARCH x64Linux4gcc7.3.0)
set(TARGET_ARCH x64Darwin17clang9.0)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    $ENV{NDDSHOME}/include 
    $ENV{NDDSHOME}/include/ndds 
    $ENV{NDDSHOME}/include/ndds/hpp
)

link_directories($ENV{NDDSHOME}/lib/${TARGET_ARCH})
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -m64 -Wall")

if(DEFINED RTI_SHARED_LIB)
    set(SHAREDLIB_SFX "")
else()
    set(SHAREDLIB_SFX "z")
    add_compile_definitions(RTI_STATIC)
endif()
if(${CMAKE_BUILD_TYPE} MATCHES "[Rr]elease")
    set(DEBUG_SFX "")
else()
    set(DEBUG_SFX "d")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -g")
endif()

#add_compile_definitions(RTI_UNIX RTI_LINUX RTI_64BIT)
add_compile_definitions(RTI_UNIX RTI_DARWIN RTI_64BIT) 

#set(SYSLIBS dl m pthread rt)
set(SYSLIBS dl m pthread)

set(CONNEXT_PRO_LIBS 
    nddscpp2${SHAREDLIB_SFX}${DEBUG_SFX} 
    nddsc${SHAREDLIB_SFX}${DEBUG_SFX} 
    nddscore${SHAREDLIB_SFX}${DEBUG_SFX}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${TARGET_ARCH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${TARGET_ARCH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${TARGET_ARCH})

set(IDL_GEN_CXX
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Point.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/PointPlugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Quaternion.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/QuaternionPlugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Pose.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/PosePlugin.cxx

)
set(IDL_GEN_H
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Point.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/PointPlugin.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Quaternion.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/QuaternionPlugin.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/Pose.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/PosePlugin.hpp
)

#add_library(type_support STATIC ${IDL_GEN_CXX} ${IDL_GEN_H})

add_executable(pose_publisher
    ${CMAKE_CURRENT_SOURCE_DIR}/pose_publisher.cxx
    ${IDL_GEN_CXX}
    ${IDL_GEN_H}
)
target_link_libraries(pose_publisher ${CONNEXT_PRO_LIBS} ${SYSLIBS})

set_target_properties(pose_publisher PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO 
)

add_executable(pose_subscriber
    ${CMAKE_CURRENT_SOURCE_DIR}/pose_subscriber.cxx
    ${IDL_GEN_CXX}
    ${IDL_GEN_H}
)
target_link_libraries(pose_subscriber ${CONNEXT_PRO_LIBS} ${SYSLIBS})

set_target_properties(pose_subscriber PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO 
)
