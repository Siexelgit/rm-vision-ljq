cmake_minimum_required(VERSION 3.8)
project(camera_publisher)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(/opt/MVS/include)
link_directories(/opt/MVS/lib/64)

add_executable(camera_publisher src/camera_publisher.cpp)

target_link_libraries(camera_publisher
  rclcpp::rclcpp
  sensor_msgs::sensor_msgs__rosidl_typesupport_cpp
  /opt/ros/jazzy/lib/libcv_bridge.so
  ${OpenCV_LIBS}
  MvCameraControl
)

target_include_directories(camera_publisher PUBLIC
  /opt/ros/jazzy/include/cv_bridge
  /opt/ros/jazzy/include/sensor_msgs
  /usr/include/opencv4
)

install(TARGETS
  camera_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()