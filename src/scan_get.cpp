#include "ros/ros.h"
#include "std_msgs/String.h"

#include "sensor_msgs/LaserScan.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include <scan_get.h>
//sensor_msgs::LaserScan  scan_data_msg;
    
 //  scan_data scan_data_buf={"hokuyo",123.0,345.897};


 void scan_callback(const sensor_msgs::LaserScan::ConstPtr& scan )
 {
      scan_data_buf.angle_min = scan ->angle_min;
      scan_data_buf.angle_max = scan->angle_max;

  //   std::cout<<scan->angle_min << scan->angle_max<< std::endl;

    std::cout<<scan_data_buf.angle_min << scan_data_buf.angle_max<< std::endl;

//     scan_data_buf.angle_increment = scan ->angle_increment;
//     scan_data_buf.time_increment = scan->time_increment;
//     scan_data_buf.scan_time = scan ->scan_time;
//     scan_data_buf.range_min = scan ->range_min;
//     scan_data_buf.range_max = scan ->range_max;
//  // udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);
 //   sendto(client_fd, (char *)&scan_data_buf, sizeof(scan_data_buf)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
//     cout << scan_data_buf.angle_increment<<endl;
//  // cout<< scan->angle_increment<< endl;
//  // ROS_INFO("I heard: [%s]", msg->data.c_str());
//  sleep(1);
 }





int main(int argc, char **argv)
{
   ros::init(argc, argv, "scan_data_get");
   ros::NodeHandle n;
   ros::Subscriber sub = n.subscribe("scan", 1, scan_callback);
    ros::spin();


  return 0;
}