# ROS2 Fundamentals Examples

A collection of fundamental ROS2 examples demonstrating core concepts and patterns for ROS2 development.

Guide create attenting the ROS2 class on youtube of Automatic Addison. 
[Link to his channel](https://www.youtube.com/@automaticaddison).

## Description

This package provides basic examples for learning ROS2 concepts, including publishers, subscribers, services, and other fundamental ROS2 patterns. The examples are written in Python and C++ to demonstrate different implementation approaches.

## Package Contents

### Python Examples
- **py_minimal_publisher.py**: A minimal ROS2 publisher node that periodically publishes "Hello World" messages to the `/py_example_topic` topic.
- **py_minimal_subscriber.py**: A minimal ROS2 subscriber node that listens to "Hello World" messages on the `/py_example_topic` topic and logs them.

### C++ Examples
- **cpp_minimal_publisher.cpp**: A minimal C++ ROS2 publisher node that publishes messages to the `/cpp_example_topic` topic at 2Hz.
- **cpp_minimal_subscriber.cpp**: A minimal C++ ROS2 subscriber node that subscribes to messages on the `/cpp_example_topic` topic.

### Scripts
- **minimal_pub_sub_launch.sh**: A bash script that launches both the Python publisher and subscriber nodes in the same terminal, demonstrating basic pub/sub communication.

## Prerequisites

- ROS2 (Jazzy or later recommended)
- Python 3.8+
- colcon build tools

## Installation

1. Clone this package into your ROS2 workspace:
   ```bash
   cd ~/ros2_ws/src
   # Copy or clone the ros2_fundamentals_examples package here
   ```

2. Build the workspace:
   ```bash
   cd ~/ros2_ws
   colcon build
   ```

3. Source the workspace:
   ```bash
   source install/setup.bash
   ```

## Usage

### Running the Python Examples

#### Option 1: Using the Launch Script
The easiest way to run both the Python publisher and subscriber together:
```bash
cd ~/ros2_ws
. install/setup.bash
cd src/ros2_fundamentals_examples/scripts
bash minimal_pub_sub_launch.sh
```

#### Option 2: Running Publisher and Subscriber Separately

**Terminal 1 - Start the publisher:**
```bash
ros2 run ros2_fundamentals_examples py_minimal_publisher
```

**Terminal 2 - Start the subscriber:**
```bash
ros2 run ros2_fundamentals_examples py_minimal_subscriber
```

You should see output like:
```
[INFO] [minimal_py_subscriber]: I heard: "Hello World: 0"
[INFO] [minimal_py_subscriber]: I heard: "Hello World: 1"
[INFO] [minimal_py_subscriber]: I heard: "Hello World: 2"
...
```

#### Option 3: Using ros2 topic echo
To see the raw messages being published:
```bash
ros2 run ros2_fundamentals_examples py_minimal_publisher
```

In another terminal:
```bash
ros2 topic echo /py_example_topic
```

### Running the C++ Examples

**Terminal 1 - Start the C++ publisher:**
```bash
ros2 run ros2_fundamentals_examples cpp_minimal_publisher
```

**Terminal 2 - Start the C++ subscriber:**
```bash
ros2 run ros2_fundamentals_examples cpp_minimal_subscriber
```

You should see output like:
```
[INFO] [cpp_minimal_publisher]: Publishing at 2Hz
[INFO] [cpp_minimal_publisher]: Publishing: 'Hello, world! 0'
[INFO] [cpp_minimal_subscriber]: I heard: Hello, world! 0
```

## Topics

### Python Examples
- `/py_example_topic` (std_msgs/String): Used for the Python publisher and subscriber examples. Publishes periodic "Hello World" messages with incrementing counter.

### C++ Examples
- `/cpp_example_topic` (std_msgs/String): Used for the C++ publisher and subscriber examples. Publishes "Hello, world!" messages with incrementing counter.

## Building from Source

To build this package:

```bash
cd ~/ros2_ws
colcon build --packages-select ros2_fundamentals_examples
```

## Testing

Run the package tests:

```bash
cd ~/ros2_ws
colcon test --packages-select ros2_fundamentals_examples
colcon test-result --verbose
```

## License

This package is licensed under the Apache-2.0 License. See the LICENSE file for details.

## Author

Alessandro Tiozzo

## ROS2 Resources

- [ROS2 Documentation](https://docs.ros.org/en/humble/)
- [ROS2 Tutorials](https://docs.ros.org/en/humble/Tutorials.html)
- [ROS2 Python API](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.html)