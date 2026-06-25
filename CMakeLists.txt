cmake_minimum_required(VERSION 3.8)
project(ros2_fundamentals_examples)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)

set(dependencies  
  rclcpp
  std_msgs
)

include_directories(
  include
)

add_executable(cpp_minimal_publisher src/cpp_minimal_publisher.cpp)
ament_target_dependencies(cpp_minimal_publisher ${dependencies})

add_executable(cpp_minimal_subscriber src/cpp_minimal_subscriber.cpp)
ament_target_dependencies(cpp_minimal_subscriber ${dependencies})

install(
  DIRECTORY ros2_fundamentals_examples scripts
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY include/
  DESTINATION include
)

# install cpp executables
install(TARGETS
  cpp_minimal_publisher
  cpp_minimal_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# install python modules for import
ament_python_install_package(${PROJECT_NAME})

# add this section to install python scripts
install(
  PROGRAMS
  ros2_fundamentals_examples/py_minimal_publisher.py
  ros2_fundamentals_examples/py_minimal_subscriber.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  # find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_pytest REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  # set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  # set(ament_cmake_cpplint_FOUND TRUE)
  # ament_lint_auto_find_test_dependencies()
  
  # py tests
  ament_add_pytest_test(py_minimal_publisher_test test/pytest/test_publisher.py TIMEOUT 60)

  # c++ tests
  ament_add_gtest(cpp_minimal_publisher_test test/gtest/test_publisher.cpp)
  # add dependencies for the c++ tests
  ament_target_dependencies(cpp_minimal_publisher_test ${dependencies})
endif()

ament_export_include_directories(include)

ament_package()