#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

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
  rclcpp::spin(std::make_shared<CounterPublisher>());
  rclcpp::shutdown();
  return 0;
}