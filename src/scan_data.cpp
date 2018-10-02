
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"


void scan_callback(const sensor_msgs::LaserScan::ConstPtr& scan )
{



    
 // ROS_INFO("I heard: [%s]", msg->data.c_str());
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "scan_data");


  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("scan", 1000, scan_callback);

  ros::spin();


  return 0;
}
