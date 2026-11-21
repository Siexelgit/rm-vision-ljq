#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"
#include "mean.h"

using Float64MultiArray = example_interfaces::msg::Float64MultiArray;

class SubscriberNode : public rclcpp::Node {
public:
    SubscriberNode() : Node("subscriber_node") {
        subscription_ = this->create_subscription<Float64MultiArray>(
            "length_topic", 10, std::bind(&SubscriberNode::topic_callback, this, std::placeholders::_1));
        mean_publisher_ = this->create_publisher<Float64MultiArray>("mean_topic", 10);
    }
private:
    void topic_callback(const Float64MultiArray::SharedPtr msg) {
        auto result = meanLength(msg->data);
        if (!result.has_value()) {
            RCLCPP_INFO(this->get_logger(), "收到空数组，不发布均值");
        } else {
            auto mean_msg = Float64MultiArray();
            mean_msg.data = {*result};
            mean_publisher_->publish(mean_msg);
            RCLCPP_INFO(this->get_logger(), "收到数据，均值：%f", *result);
        }
    }
    rclcpp::Subscription<Float64MultiArray>::SharedPtr subscription_;
    rclcpp::Publisher<Float64MultiArray>::SharedPtr mean_publisher_;
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}