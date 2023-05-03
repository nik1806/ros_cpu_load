FROM ubuntu:20.04

# Set variables
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENV DEBIAN_FRONTEND=noninteractive

# Setup source 
RUN apt update && \
    apt install -y curl gnupg2 lsb-release

# Add  GPG key and repo to source list
RUN apt update && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install ROS2 Foxy
RUN apt update && \
    apt upgrade && \
    apt install ros-foxy-desktop python3-argcomplete -y

# Source ROS2 setup files
RUN echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc

# Start a bash shell when container start
CMD ["/bin/bash"]
