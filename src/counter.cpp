#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "moos-ros-bridge/MsgContainer.h"

using namespace std::chrono_literals;

// A simple counter node that publishes a counter as an int32 at an interval of 10000ms

class CounterPublisher : public rclcpp::Node
{
  public:
    CounterPublisher()
    : Node("ros_counter"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::Int32>("CounterFromROS", 10);
      timer_ = this->create_wall_timer(
      1000ms, std::bind(&CounterPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Int32();
      message.data = count_++;
      RCLCPP_INFO(this->get_logger(), "Counting: '%i'", message.data);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto publisher_node = std::make_shared<CounterPublisher>();
  auto another_pub = publisher_node->create_publisher<std_msgs::msg::Int32>("publisher_node", 10);

  auto container = ContainerBase<std_msgs::msg::Int32>(
    publisher_node,
    "new_moosName", 
		"new_rosName", 
		"new_moosType", 
		"new_rosType"
    );
  auto int_message = std_msgs::msg::Int32();
  int_message.data = 12;
  container.pub->publish(int_message);

  
  // (another_pub,"name","mane","mane","mane");


  // RCLCPP_INFO(this->get_logger());
  rclcpp::spin(publisher_node);
  rclcpp::shutdown();
  
  return 0;
}