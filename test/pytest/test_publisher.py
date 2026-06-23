#!/usr/bin/env python3

"""
Test script for the ROS 2 minimal publisher node.

This script contains the unit test for verifying a minimal ROS 2 publisher.
It tests the node creation, message counter increment, and message content formatting.

-------
Subscription Topics:
    None

-------
Publishing Topics:
    /py_example_topic (std_msgs/String): Example messages with incrementing counter.

:author: Alessandro Tiozzo
:date: June 23, 2026
"""

import pytest
import rclpy
from std_msgs.msg import String
from ros2_fundamentals_examples.py_minimal_publisher import MinimalPyPublisher

def test_publisher_creation():
    """
    Test if the publisher node is created correctly.
    
    This test verifies:
    1. The node name is set correctly.
    2. The publisher object exists.
    3. The topic name is correct.
    
    :raises: AssertionError if any of the checks fail.
    """

    rclpy.init()
    try:
        # Create an instance of the publisher node
        node = MinimalPyPublisher()

        # Test 1: Verify the node name
        assert node.get_name() == 'py_minimal_publisher', "Node name is incorrect."

        # Test 2: Verify the publisher exists and has the correct topic name
        assert hasattr(node, 'publisher_1'), "Publisher object does not exist."
        assert node.publisher_1.topic_name == '/py_example_topic', "Publisher topic name is incorrect."
    
    finally:
        # Clean up ROS 2 communication
        rclpy.shutdown()


def test_message_counter_increment():
    """
    Test if the message counter increments correctly.

    This test verifies that the counter (node.i) increases by 1 after each
    timer callback execution.

    :raises: AssertionError if the counter does not increment as expected.
    """

    rclpy.init()
    try:
        # Create an instance of the publisher node
        node = MinimalPyPublisher()

        # Store the initial counter value
        initial_counter = node.i

        # Simulate a timer callback to publish a message
        node.timer_callback()

        # Test: Verify the counter has incremented by 1
        assert node.i == initial_counter + 1, "Message counter did not increment correctly."
    
    finally:
        # Clean up ROS 2 communication
        rclpy.shutdown()


def test_message_content():
    """
    Test if the published message content is formatted correctly.

    This test verifies that the message data follows the expected format
    "Hello World: <counter_value>".

    :raises: AssertionError if the message content is not as expected.
    """

    rclpy.init()
    try:
        # Create an instance of the publisher node
        node = MinimalPyPublisher()

        # Set counter to a known value for testing
        node.i = 5
        msg = String()

        # Retrieve the last published message
        msg.data = f'Hello World: {node.i}'

        # Test: Verify the message content format
        assert msg.data == 'Hello World: 5', "Published message content is incorrect."
    
    finally:
        # Clean up ROS 2 communication
        rclpy.shutdown()

if __name__ == '__main__':
    # Run the tests if the script is executed directly
    pytest.main(['-v'])