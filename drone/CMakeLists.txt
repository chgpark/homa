cmake_minimum_required(VERSION 2.8.3)
project(drone)

find_package(catkin REQUIRED COMPONENTS
  mavros
  roscpp
  rospy
  std_msgs
  sensor_msgs
  mavros_msgs
  image_geometry
  geometry_msgs
#  message_generation
)

catkin_package(
)

set(drone_class
  lib/drone.h
  lib/drone.cpp
)

set(pid_class
    lib/MiniPID/MiniPID.h
    lib/MiniPID/MiniPID.cpp
)

set(lowpass_class
    lib/LowPassFilter/LowPassFilter.cpp
    lib/LowPassFilter/LowPassFilter.hpp
)


include_directories(include ${catkin_INCLUDE_DIRS}
    )

add_executable(ctrl_att ctrl_att.cpp lib/conf.h lib/UTM.cpp ${endrun_class} ${pid_class}
    ${lowpass_class} ${endrun_wrapper_arduino})

#FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /home/url/catkin_ws/prereq/wiringPi)

add_dependencies(ctrl_att ${${PROJECT_NAME}_EXPORTED_TARGET} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ctrl_att ${catkin_LIBRARIES})
