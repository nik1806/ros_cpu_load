#!/bin/bash

ROS2_WS_PATH=ros2_ws

cd $ROS2_WS_PATH
colcon build

source /opt/ros/foxy/setup.bash

. install/setup.bash

# Launch the publisher node in the background
ros2 run cpu_pubsub talker &

# Launch the subscriber node in the foreground
ros2 run cpu_pubsub listener
