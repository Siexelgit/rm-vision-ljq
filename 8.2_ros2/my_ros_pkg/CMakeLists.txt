cmake_minimum_required(VERSION 3.8)
project(my_ros_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

include_directories(include)
add_library(mylib STATIC src/mean.cpp)

add_executable(publisher_node src/publisher_node.cpp)
target_link_libraries(publisher_node rclcpp::rclcpp example_interfaces::example_interfaces__rosidl_typesupport_cpp)

add_executable(subscriber_node src/subscriber_node.cpp)
target_link_libraries(subscriber_node mylib rclcpp::rclcpp example_interfaces::example_interfaces__rosidl_typesupport_cpp)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  publisher_node
  subscriber_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
  OPTIONAL
)
install(DIRECTORY
  include/
  DESTINATION include
  OPTIONAL
)
install(FILES
  package.xml
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
