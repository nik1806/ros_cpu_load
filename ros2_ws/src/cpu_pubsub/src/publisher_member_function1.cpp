#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals;

class CPULoadNode : public rclcpp::Node {
public:
  CPULoadNode() : Node("cpu_load_node") {
    // Create publisher for CPU load data
    pub_ = this->create_publisher<std_msgs::msg::Float64>("cpu_load", 10);

    // Create log file for CPU load data
    log_file_.open("cpu_load.log", std::ios_base::app);
  }

  void timerCallback() {
    publishCPULoad();
  }

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pub_;
  std::ofstream log_file_;

  void publishCPULoad() {
    // Get current CPU load and publish it
    double cpu_load = getCurrentCPULoad();
    
    std_msgs::msg::Float64 msg;
    msg.data = cpu_load;
    pub_->publish(msg);

    // Write CPU load data to log file
    log_file_ << cpu_load << std::endl;
  }

  // double getCurrentCPULoad() {
  //   // Parse CPU load data from line
  //   std::vector<double> values;

  //   // Read CPU load data from /proc/stat file
  //   std::ifstream stat_file("/proc/stat");
    
  //   std::string line;
  //   if (std::getline(stat_file, line)) {
  //       // process the data
  //       std::stringstream ss(line);
  //       std::string cpu;
  //       int value;
  //       ss >> cpu;
        
  //       while (ss >> value) {
  //         values.push_back(value);    
  //       }
  //   } else {
  //       std::cerr << "Error: Failed to read line from /proc/stat" << std::endl;
  //       return -1.0;
  //   }
  //   stat_file.close();

  //   // Calculate CPU load as relative value
  //   double total_time = values[1] + values[2] + values[3] + values[4];
  //   double idle_time = values[3];
  //   return (total_time - idle_time) / total_time;
  // }

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
    // return std::to_string(cpu_load);
  }

};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CPULoadNode>();
  auto timer = node->create_wall_timer(5s, std::bind(&CPULoadNode::timerCallback, node));
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
