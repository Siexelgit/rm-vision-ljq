#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include "MvCameraControl.h"

class HikCameraNode : public rclcpp::Node {
public:
    HikCameraNode() : Node("camera_publisher"), handle_(nullptr) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image_raw", 10);
        MV_CC_Initialize();
        if (!init_camera()) {
            RCLCPP_ERROR(this->get_logger(), "Camera init failed!");
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Camera started!");
        grab_thread_ = std::thread(&HikCameraNode::grab_loop, this);
    }

    ~HikCameraNode() {
        if (handle_) {
            MV_CC_StopGrabbing(handle_);
            MV_CC_CloseDevice(handle_);
            MV_CC_DestroyHandle(handle_);
        }
        MV_CC_Finalize();
        if (grab_thread_.joinable()) grab_thread_.join();
    }

private:
    bool init_camera() {
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet || stDeviceList.nDeviceNum == 0) return false;
        nRet = MV_CC_CreateHandle(&handle_, stDeviceList.pDeviceInfo[0]);
        if (MV_OK != nRet) return false;
        nRet = MV_CC_OpenDevice(handle_);
        if (MV_OK != nRet) return false;
                MV_CC_SetEnumValue(handle_, "PixelFormat", PixelType_Gvsp_BGR8_Packed);
        MV_CC_SetEnumValue(handle_, "TriggerMode", 0);
        nRet = MV_CC_StartGrabbing(handle_);
        return MV_OK == nRet;
    }

    void grab_loop() {
        MV_FRAME_OUT stImageInfo = {0};
        while (rclcpp::ok()) {
            int nRet = MV_CC_GetImageBuffer(handle_, &stImageInfo, 1000);
            if (nRet == MV_OK) {
                cv::Mat frame(stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nWidth, CV_8UC3, stImageInfo.pBufAddr);
                std_msgs::msg::Header header;
                header.stamp = this->now();
                header.frame_id = "camera_link";
                auto msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
                publisher_->publish(*msg);
                cv::imwrite("/home/siexel-luo/saved_frame.jpg", frame);
                MV_CC_FreeImageBuffer(handle_, &stImageInfo);
            }
        }
    }

    void* handle_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    std::thread grab_thread_;
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HikCameraNode>());
    rclcpp::shutdown();
    return 0;
}