#! /usr/bin/env python3

"""
Description:
    This ROS2 node periodically publishes "Hello World" messages to a topic.

------
Publishing Topics:
    This channel containing the "Hello World" messages
    /py_example_topic - std_msgs/String

Subscription Topics:
    None

------
Author: Alessandro Tiozzo
Date: April 17, 2026
"""

import rclpy # import the ROS 2 client library for python
from rclpy.node import Node # import the Node class, used for creating nodes

from std_msgs.msg import String # import String message type for ROS 2

class MinimalPyPublisher(Node):
    """Create a minimal publisher node
    """
    
    def __init__(self):
        """Create a custom node class for pubblishing messages        
        """
        
        # initialize the node with a name
        super().__init__('minimal_py_publisher')

        # create a publisher on the topic with a queue size of 10 messages
        self.publisher_1 = self.create_publisher(String, '/py_example_topic', 10)

        # create a timer with a period of 00.5 seconds to trigger pubblishing of message
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)

        # initialize a counter variable for message content
        self.i = 0
    
    def timer_callback(self):
        """Callback function executed periodically by timer
        """

        # create a new String message object
        msg = String()

        # set the message data with a counter
        msg.data = 'Hello World: %d' % self.i

        # publish the messae you created above to a topic
        self.publisher_1.publish(msg)

        # log a message indicating the message has been published
        self.get_logger().info('Publishing: %s' % msg.data)

        self.i += 1

def main(args = None):
    """Main function to start the ROS 2 node
    
    Args:
        args (List, optional): Command-line arguments. Default to none.
    """

    rclpy.init(args = args)

    # create an instance of the Minimal Publisher node
    minimal_py_publisher = MinimalPyPublisher()

    # run the node
    rclpy.spin(minimal_py_publisher)

    # destroy the node explicitly
    minimal_py_publisher.destroy_node()

    # shutdown ROS 2 communication
    rclpy.shutdown()

if __name__ == '__main__':
    # execute the main function if the script is run directly
    main()