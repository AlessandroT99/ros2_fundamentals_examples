/**
 * @file cpp_minimal_subscriber.cpp
 * @author Alessandro Tiozzo
 * @brief A minimal ROS 2 C++ subscriber node that subscribes to a topic and prints received messages.
 * @version 0.1
 * @date 2026-06-23
 * 
 * ------
 * Subscription Topics:
 *  String message: /cpp_example_topic - std_msgs/String
 * ------
 * Publisher Topics:
 *  None
 * 
 */

#include "rclcpp/rclcpp.hpp" // ROS 2 C++ client library
#include "std_msgs/msg/string.hpp" // Standard message type for strings

using std::placeholders::_1; // For using placeholders in callbacks
using namespace std::chrono_literals; // For using time literals

class CppMinimalSubscriber : public rclcpp::Node {
public:
    CppMinimalSubscriber() : Node("cpp_minimal_subscriber") {
        // Create a subscription to the "topic" topic with a queue size of 10
        subscriber_ = create_subscription<std_msgs::msg::String>(
            "/cpp_example_topic",
            10,
            std::bind(&CppMinimalSubscriber::topicCallback, this, _1)
        );

        RCLCPP_INFO(get_logger(), "Subscribed to /cpp_example_topic");
    }

    void topicCallback(const std_msgs::msg::String & message) {
        RCLCPP_INFO_STREAM(get_logger(), "I heard: " << message.data.c_str());
    }  

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_; // Subscriber object
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv); // Initialize the ROS 2 system

    auto cpp_minimal_subscriber_node = std::make_shared<CppMinimalSubscriber>(); // Create the subscriber node
    rclcpp::spin(cpp_minimal_subscriber_node); // Spin the node

    rclcpp::shutdown(); // Shutdown the ROS 2 system

    return 0;
}