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

#include <scan_get.h>
//sensor_msgs::LaserScan  scan_data_msg;

extern struct scan_data scan_data_buf;


int client_fd;
struct sockaddr_in ser_addr;
#define SERVER_PORT 8888

 void scan_callback(const sensor_msgs::LaserScan::ConstPtr& scan )
 {
  //   scan_data_buf_frame_id = scan ->header.frame_id;
  //     scan_data_buf.frame_id = "hokuyo";

      scan_data_buf.angle_min = scan ->angle_min;
      scan_data_buf.angle_max = scan ->angle_max;
      scan_data_buf.angle_increment = scan ->angle_increment;
     scan_data_buf.time_increment = scan->time_increment;
     scan_data_buf.scan_time = scan ->scan_time;
     scan_data_buf.range_min = scan ->range_min;
     scan_data_buf.range_max = scan ->range_max;


; 
  //   std::cout<<scan->angle_min << scan->angle_max<< std::endl;

//  // ROS_INFO("I heard: [%s]", msg->data.c_str());
//  sleep(1);
 }

void *scan_get( void *arg )
{
   // udp 
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
      //  return -1;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
    ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换
  //  close(client_fd);
  while(ros::ok())
      {
        std::cout<<".....pppppppppppppppppppppppppppppppp..."<<scan_data_buf.angle_min ;
        std::cout<<"   "<<scan_data_buf.angle_max<< "  "<< scan_data_buf.scan_time<<std::endl;
  sendto(client_fd, (char *)&scan_data_buf, sizeof(scan_data_buf)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

    //   sleep(1);
     }
}
void create_all_thread(void)
{
	pthread_t thread_scan_get;
	if( (pthread_create( &thread_scan_get , NULL , scan_get, NULL )) != 0 )
	{
		perror("Create the thread_joy fail");
		exit( 1 );
	}
}



int main(int argc, char **argv)
{
   ros::init(argc, argv, "scan_data_get");
   ros::NodeHandle n;
   ros::Subscriber sub = n.subscribe("scan", 1, scan_callback);
   create_all_thread();
    ros::spin();


  return 0;
}
