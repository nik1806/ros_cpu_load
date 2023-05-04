# Spleenlab_testwork
TASK OVERVIEW 

## 1. Dockerfile
ADD SHORT DESCRIPTION OF APPROACH
### Command to build docker image

``` docker build -t ros2img .```

### To run the container
We are mounting ros workspace here as well.

``` 
docker run \
    -v $(pwd)/ros2_ws:/root/ros2_ws \
    -v /proc:/root/proc \
    -it ros2img 
```

To open another terminal connected to the same container
``` docker exec -it <container_id> bash ```

use `docker ps` to get `<container_id>`

#### Instructions for creating a publisher-subscriber

```
# create package
ros2 pkg create --build-type ament_cmake cpp_pubsub 

# check missing dependencies
rosdep install -i --from-path src --rosdistro foxy -y 

# build package
colcon build --packages-select cpu_pubsub 

cd ros2_ws

. install/setup.bash

# publish cpu_load on a topic
ros2 run cpu_pubsub talker

# read from topic and log into a file
ros2 run cpu_pubsub listener

```
