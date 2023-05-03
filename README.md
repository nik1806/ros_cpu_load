# Spleenlab_testwork
TASK OVERVIEW 

## 1. Dockerfile
ADD SHORT DESCRIPTION OF APPROACH
### Command to build docker image

``` docker build -t ros2img .```

### To run the container
We are mounting ros workspace here as well.

``` docker run -v $(pwd)/ros_ws:/root/ros_ws -it ros2img ```

To open another terminal connected to the same container
``` docker exec -it <container_id> bash ```

use `docker ps` to get `<container_id>`