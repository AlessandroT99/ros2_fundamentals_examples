/**
 * @file cpp_minimal_publisher.cpp
 * @author Alessandro Tiozzo
 * @brief A minimal ROS 2 C++ publisher node that publishes messages to a topic.
 * @version 0.1
 * @date 2026-06-23
 * 
 * ------
 * Subscription Topics:
 *  None
 * ------
 * Publisher Topics:
 *  String message: /cpp_example_topic - std_msgs/String
 * 
 */

#include "rclcpp/rclcpp.hpp" // ROS 2 C++ client library
#include "std_msgs/msg/string.hpp" // Standard message type for strings

using namespace std::chrono_literals; // For using time literals

class CppMinimalPublisher : public rclcpp::Node {
public:
    CppMinimalPublisher() : Node("cpp_minimal_publisher"), count_(0) {
        // Create a publisher for the "topic" topic with a queue size of 10
        publisher_ = create_publisher<std_msgs::msg::String>("/cpp_example_topic", 10); 
        timer_ = create_wall_timer(
            500ms, 
            std::bind(&CppMinimalPublisher::timer_callback, this)
        );

        RCLCPP_INFO(get_logger(), "Publishing at 2Hz");
    }

    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count_++);
        publisher_->publish(message);
        RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.data.c_str());
    }

private:
    size_t count_; // Counter for the number of messages published
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // Publisher object
    rclcpp::TimerBase::SharedPtr timer_; // Timer object
};

#ifndef TESTING_EXCLUDE_MAIN
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv); // Initialize the ROS 2 system
 
    auto cpp_minimal_publisher_node = std::make_shared<CppMinimalPublisher>(); // Create the publisher node
    rclcpp::spin(cpp_minimal_publisher_node); // Spin the node
 
    rclcpp::shutdown(); // Shutdown the ROS 2 system
 
    return 0;
}
#endif