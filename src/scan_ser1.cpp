//xx

#include "ros/ros.h"
#include "std_msgs/String.h"

#include "sensor_msgs/LaserScan.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8888

struct scan_data
{
 // std::string  frame_id;
   char frame_id[10];
  float angle_min;       
  float angle_max;        
  float angle_increment;  
  float time_increment;                                                  
  float scan_time;       
  float range_min;      
  float range_max; 
  float ranges[897];
  float intensities[897];
};

struct scan_data scan_data_buf;
ros::Publisher scan_pub;
ros::Time current_time;
sensor_msgs::LaserScan  scan_msg;

#define BUFF_LEN 4096

void *pub_scan_msg(void *arg)
{  
    //ros::NodeHandle n1;
    while(ros::ok())
    {
    current_time = ros::Time::now();
    scan_msg.header.stamp = current_time;
    scan_msg.header.frame_id = "hokuyo";
    // scan_msg.angle_min = scan_data_buf.angle_min;
    // scan_msg.angle_max = scan_data_buf.angle_max;
    // scan_msg.angle_increment = scan_data_buf.angle_increment;
    // scan_msg.time_increment = scan_data_buf.time_increment;
    // scan_msg.scan_time = scan_data_buf.scan_time;
    // scan_msg.range_min = scan_data_buf.range_min;
    // scan_msg.range_max = scan_data_buf.range_max;

    scan_msg.angle_min = 1;
    scan_msg.angle_max = 2;
    scan_msg.angle_increment = 3;
    scan_msg.time_increment = 4;
    scan_msg.scan_time = 5;
    scan_msg.range_min = 6;
    scan_msg.range_max = 7;
   // std::copy(scan_data_buf.ranges.begin(), scan_data_buf.ranges.end(),scan_msg.ranges)
    scan_msg.ranges ={0};
    scan_msg.intensities = {0};
    scan_pub.publish(scan_msg);

    }

}

void *scan_get( void *arg )
{
    int server_fd, ret;
    
    struct sockaddr_in ser_addr; 

    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
     //   return -1;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  //  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换
    ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret < 0)
    {
        printf("socket bind fail!\n");
      //  return -1;  //scan_pub.publish(scan_msg);

    }
   // close(server_fd);
    char buf[BUFF_LEN] = {0};  //接收缓冲区，1024字节
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
    while(ros::ok())
    {
        len = sizeof(clent_addr);
        count = recvfrom(server_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count == -1)
        {
            printf("recieve data fail!\n");
          //  return;
        }     
        memcpy(&scan_data_buf,buf,sizeof(scan_data_buf)+1);
   //    std::cout<<"scan_data_buf:   "<<scan_data_buf.frame_id;
        std::cout<<scan_data_buf.ranges[0]<<"  "<<scan_data_buf.intensities[0]<< std::endl;

    }
}

void create_all_thread(void)
{
	pthread_t thread_scan_get;
    pthread_t thread_pub_scan;
	if( (pthread_create( &thread_scan_get , NULL , scan_get, NULL )) != 0 )
	{
		perror("Create the thread_joy fail");
		exit( 1 );
	}
    // if( (pthread_create( &thread_pub_scan , NULL , pub_scan_msg, NULL )) != 0 )
	// {
	// 	perror("Create the thread_joy fail");
	// 	exit( 1 );
	// }

}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "scan_ser1");
  ros::NodeHandle n;
  //  create_all_thread();
  //ros::Subscriber sub = n.subscribe("scan", 1, scan_callback);
  scan_pub = n.advertise<sensor_msgs::LaserScan>("scan1",100);
  //scan_pub.publish(scan_msg);
     ros::Rate loop_rate(10);

   current_time = ros::Time::now();
    scan_msg.header.stamp = current_time;
    scan_msg.header.frame_id = "hokuyo";
    // scan_msg.angle_min = scan_data_buf.angle_min;
    // scan_msg.angle_max = scan_data_buf.angle_max;
    // scan_msg.angle_increment = scan_data_buf.angle_increment;
    // scan_msg.time_increment = scan_data_buf.time_increment;
    // scan_msg.scan_time = scan_data_buf.scan_time;
    // scan_msg.range_min = scan_data_buf.range_min;
    // scan_msg.range_max = scan_data_buf.range_max;

    scan_msg.angle_min = 1;
    scan_msg.angle_max = 2;
    scan_msg.angle_increment = 3;
    scan_msg.time_increment = 4;
    scan_msg.scan_time = 5;
    scan_msg.range_min = 6;
    scan_msg.range_max = 7;
   // std::copy(scan_data_buf.ranges.begin(), scan_data_buf.ranges.end(),scan_msg.ranges)
    scan_msg.ranges ={0};
    scan_msg.intensities = {0};
    while(ros::ok())
    {
        scan_pub.publish(scan_msg);

    }


   create_all_thread();
  ros::spin();
  //ros::spinOnce();


  return 0;
}
