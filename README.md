一.建构与运行的命令
8.1 cpp&cmake
mkdir build &&cd build
cmake ..
make
./test_main

8.2
将8.2_ros2重命名为my_ros_pkg 并放入你的 ros2_ws/src 目录下。
在工作空间目录下执行：
colcon build --packages-select my_ros_pkg
source install/setup.bash

终端 1（运行发布者）：
export ROS_LOCALHOST_ONLY=1
ros2 run my_ros_pkg publisher_node

终端 2（运行订阅者）：
export ROS_LOCALHOST_ONLY=1
ros2 run my_ros_pkg subscriber_node

二.节点运行


发布节点：节点名 publisher_node，话题名 length_topic，消息类型 example_interfaces/msg/Float64MultiArray。
均值节点（订阅者）：节点名 subscriber_node，订阅话题 length_topic，发布话题 mean_topic，消息类型 example_interfaces/msg/Float64MultiArray。

运行输出表现：
发布端输出：
[INFO] 发送：空数组
[INFO] 发送：1.0 2.0 3.0 4.0
[INFO] 发送：5.0 5.0 5.0

订阅端输出：
[INFO] 收到空数组，不发布均值
[INFO] 收到数据，均值：2.500000
[INFO] 收到数据，均值：5.000000

三.为何不返回0？
0是合法长度数值，若空数组也返回0,易和计算算出的平均值混淆。因此使用
std::optional，在空数组时返回nullopt

四.问题以及解决
cpp编译是无法找到mean.h
文件路径没有统一
修改了文件路径，移动了一下mean.h的位置就好了
