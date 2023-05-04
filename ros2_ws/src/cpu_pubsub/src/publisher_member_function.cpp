#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <thread>
#include <memory>

#include "rclcpp/rclcpp.hpp" // allow to use ROS2 system
#include "std_msgs/msg/float64.hpp" // built-in message type to publish data
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;


class CPULoadNodePub : public rclcpp::Node {
public: 
  CPULoadNodePub() : Node("cpu_load_node_pub") {
      // Create publisher for CPU load data
      publisher_ = this->create_publisher<std_msgs::msg::Float64>("cpu_load", 10);
      timer_ = this->create_wall_timer(5s, std::bind(&CPULoadNodePub::timerCallback, this));
  }

  void timerCallback() {
    publishCPULoad();
  }

private: 
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

  double getCurrentCPULoad() {
    // Read CPU load data from /proc/stat file
    std::ifstream stat_file("/proc/stat");
    std::string line;
    std::getline(stat_file, line);
    stat_file.close();

    // Extract CPU load values from first line of /proc/stat file
    std::stringstream ss(line);
    std::string cpu;
    ss >> cpu;
    int user, nice, sys, idle, iowait, irq, softirq, steal, guest, guest_nice;
    ss >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

    // Calculate total CPU time and idle time
    int total_time = user + nice + sys + idle + iowait + irq + softirq + steal;
    int idle_time = idle + iowait;

    // Calculate CPU load as percentage
    double cpu_load = 100.0 * (total_time - idle_time) / total_time;
    return cpu_load;
  }

  void publishCPULoad() {
    // Get current CPU load and publish it
    double cpu_load = getCurrentCPULoad();
    std_msgs::msg::Float64 msg;
    msg.data = cpu_load;
    // std::cout << cpu_load << std::endl;
    publisher_->publish(msg);
  }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); // init ROS2
  rclcpp::spin(std::make_shared<CPULoadNodePub>()); 
  rclcpp::shutdown();
  return 0;
}
