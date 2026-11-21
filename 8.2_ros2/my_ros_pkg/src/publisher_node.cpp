#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;
using Float64MultiArray = example_interfaces::msg::Float64MultiArray;

class PublisherNode : public rclcpp::Node {
public:
    PublisherNode() : Node("publisher_node"), count_(0) {
        publisher_ = this->create_publisher<Float64MultiArray>("length_topic", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&PublisherNode::timer_callback, this));
    }
private:
    void timer_callback() {
        auto msg = Float64MultiArray();
        if (count_ % 3 == 0) {
            msg.data = {};
            RCLCPP_INFO(this->get_logger(), "发送：空数组");
        } else if (count_ % 3 == 1) {
            msg.data = {1.0, 2.0, 3.0, 4.0};
            RCLCPP_INFO(this->get_logger(), "发送：1.0 2.0 3.0 4.0");
        } else {
            msg.data = {5.0, 5.0, 5.0};
            RCLCPP_INFO(this->get_logger(), "发送：5.0 5.0 5.0");
        }
        publisher_->publish(msg);
        count_++;
    }
    rclcpp::Publisher<Float64MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}