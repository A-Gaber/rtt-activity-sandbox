cmake_minimum_required(VERSION 2.8.3)
project(rtt-activity-sandbox)

set(CMAKE_BUILD_TYPE Debug)#Release

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-omit-frame-pointer -g -finstrument-functions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OROCOS-RTT REQUIRED)
if (NOT OROCOS-RTT_FOUND)
  message (FATAL_ERROR "\nCould not find Orocos-RTT. Please use the shell command\n 'source orocos_toolchain/env.sh' and then run cmake again.")
endif()

include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

# set (Eigen_INCLUDE_DIRS "/usr/include/eigen3")

# find_package(Boost COMPONENTS thread REQUIRED)

# find_package(RST-RT REQUIRED)
# message(STATUS "RST-RT version: ${RST-RT_VERSION}")
# include_directories(BEFORE SYSTEM ${RST-RT_INCLUDE_DIRS})
# add_definitions(${RST-RT_CFLAGS})
# link_directories(${RST-RT_LIBRARY_DIR} ${RST-RT_LIBRARY_DIRS})

include_directories(
    include
    src
    # ${Boost_INCLUDE_DIR}
    # ${Eigen_INCLUDE_DIRS}
    ${USE_OROCOS_INCLUDE_DIRS}
    # ${RST-RT_INCLUDE_DIRS}
)

orocos_component(${PROJECT_NAME} 
  src/Master.cpp
  src/Sender.cpp
  src/Receiver.cpp
)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS RTT_COMPONENT)

target_link_libraries(${PROJECT_NAME}
   ${USE_OROCOS_LIBRARIES}
   ${OROCOS-RTT_LIBRARIES}
  #  ${Boost_LIBRARIES}
  #  ${RST-RT_LIBRARIES}
)

orocos_generate_package()