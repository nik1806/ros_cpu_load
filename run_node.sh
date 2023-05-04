#!/bin/bash

ROS2_WS_PATH=ros2_ws

cd $ROS2_WS_PATH
# build package
colcon build

# source ros
source /opt/ros/foxy/setup.bash

# source env
. install/setup.bash

# Launch the publisher node in the background
ros2 run cpu_pubsub talker &

# Launch the subscriber node in the foreground
ros2 run cpu_pubsub listener
