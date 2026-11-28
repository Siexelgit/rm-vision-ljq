第三讲
1.程序运行
cd ~/ros2_ws
colcon build --packages-select camera_publisher
source install/setup.bash
ros2 run camera_publisher camera_publisher

2.相机与节点
相机：MV-CS016-10UC
采集接口：USB
发布话题：/image_raw
QoS：队列深度10 其余默认
间戳来源：ROS 2 节点系统时间 this->now()

3.同帧留样
话题名：/image
分辨率：1440*1080
发布编码：bgr8
保存格式：.PNG
header.stamp: 使用相机时忘记回溯，无法得到真实值
header.frame_id: camera_link

