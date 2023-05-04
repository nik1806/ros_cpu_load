#include <memory>
#include <fstream>
#include <chrono>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

using std::placeholders::_1;

class CPULoadNodeSub : public rclcpp::Node
{
public:
  CPULoadNodeSub()
  : Node("cpu_load_node_sub")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Float64>(
      "cpu_load", 10, std::bind(&CPULoadNodeSub::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::Float64::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%lf'", msg->data);
    // Write CPU load data to log file
    static std::ofstream ofs("cpu_load.log", std::ios_base::app);
    // ofs << msg->data << std::endl;
  }
  
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CPULoadNodeSub>());  
  rclcpp::shutdown();
  return 0;
}
