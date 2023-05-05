#!/bin/bash

ROS2_WS_PATH=/root/ros2_ws

cd $ROS2_WS_PATH

# apt install ros-foxy-ament-package

# source ros
source /opt/ros/foxy/setup.bash

# check dependencies
rosdep install -i --from-path src --rosdistro foxy -y 
# build package
colcon build --packages-select cpu_pubsub 

# source env
. install/setup.bash

# Launch the publisher node in the background
ros2 run cpu_pubsub talker &

# Launch the subscriber node in the foreground
ros2 run cpu_pubsub listener
