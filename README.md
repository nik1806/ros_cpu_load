# Spleenlab_testwork
I have created a ros package to write cpu log into a `log` file, the ros node automatically runs inside a container.
To configure the container and run it automatically I have created a docker compose `yaml` file. Finally, to simulate 
the cpu load and to read it outside the docker additional shell scripts are created. 

## Automantically start container
We are using docker compose for this functionality.
```
docker compose up -d 
```
`-d` to detach our screen from the output. We can remove this to see the output from docker.

## Load CPU sufficiently to test our pipeline
```
chmod +x increase_load_cpu.sh

./increase_load_cpu.sh
```
We only need to give executable permission once.
After we run the script, we will observe that CPU load increases.

## Read and print log file outside docker
```
chmod +x read_n_print_log.sh

./read_n_print_log.sh
```
This will start printing every new value written into our log file.

## Relevant instructions to debug
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
ros2 pkg create --build-type ament_cmake cpu_pubsub 

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
