#! /usr/bin/env python3

"""
Description: 
    This ROS 2 node subcribes to "Hello World" messages.

--------
Publishing Topics:
    None
--------
Subscribing Topics:
    The channel containing the "Hello World" messages.
    /py_example_topic - std_msgs/String

Author: Alessandro Tiozzo
Date: June 22, 2026

"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPySubscriber(Node):
    def __init__(self):
        # initialize the node with a name
        super().__init__('py_minimal_subscriber')

        # create a subscriber on the topic with a queue size of 10 messages
        self.subscriber_1 = self.create_subscription(
            String,
            '/py_example_topic',
            self.listener_callback,
            10)

    def listener_callback(self, msg):
        # log the message data received from the topic
        self.get_logger().info(f'I heard: "{msg.data}"')

def main(args=None):
    # initialize the ROS 2 python client library
    rclpy.init(args=args)

    # create the node object
    py_minimal_subscriber = MinimalPySubscriber()

    # keep the node running and listening for messages
    rclpy.spin(py_minimal_subscriber)

    # destroy the node explicitly
    py_minimal_subscriber.destroy_node()

    # shutdown the ROS 2 python client library
    rclpy.shutdown()

if __name__ == '__main__':
    # execute the main function if the script is run directly
    main()