/**
 * @file test_publisher.cpp
 * @brief Unit test for the ROS 2 minimal publisher node.
 * 
 * This file contains test cases to verify the functionality of our minimal publisher node.
 * We test two main things:
 * 1. The publisher node can be created successfully with the right name and topic.
 * 2. The publisher node can publish messages with "Hello World: <counter_value>".
 * 
 * Testing framework:
 *  Google Test (gtest) is used for writing and running the unit tests in C++.
 * 
 * Tests:
 *  TestNodeCreation: Verifies node name and publisher setup.
 *  TestMessageContent: Verifies published message format.
 * 
 * @author Alessandro Tiozzo
 * @date 2026-06-24
*/

#include <gtest/gtest.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class CppMinimalPublisher;

// Exclude the main function in the publisher node during testing
#define TESTING_EXCLUDE_MAIN 
#include "../../src/cpp_minimal_publisher.cpp"


class TestMinimalPublisher : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize ROS 2
        rclcpp::init(0, nullptr);

        node = std::make_shared<CppMinimalPublisher>();
    }

    void TearDown() override {
        // Shutdown ROS 2
        rclcpp::shutdown();
    }

    std::shared_ptr<CppMinimalPublisher> node;
};

TEST_F(TestMinimalPublisher, TestNodeCreation) {
    // Verify that the node was created successfully
    EXPECT_EQ(std::string(node->get_name()), std::string("cpp_minimal_publisher"));

    // Verify that the publisher is set up correctly and is unique
    auto pub_endpoints = node->get_publishers_info_by_topic("/cpp_example_topic");
    EXPECT_EQ(pub_endpoints.size(), 1);
}

TEST_F(TestMinimalPublisher, TestMessageContent) {
    // Create a message and publish it
    std::shared_ptr<std_msgs::msg::String> received_message;
    
    auto subscription = node->create_subscription<std_msgs::msg::String>(
        "/cpp_example_topic",
        10,
        [&received_message](std_msgs::msg::String::SharedPtr msg) {
            received_message = std::make_shared<std_msgs::msg::String>(*msg);
        }
    );

    node->timer_callback(); // Trigger the timer callback to publish a message
    rclcpp::spin_some(node); // Process the callback to receive the message

    // Verify that the published message has the expected content
    EXPECT_EQ(received_message->data.substr(0,12), "Hello, world");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}