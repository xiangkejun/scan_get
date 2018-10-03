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


#define BUFF_LEN 4096

void handle_udp_msg(int fd)
{
    char buf[BUFF_LEN] = {0};  //接收缓冲区，1024字节
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
    while(ros::ok())
  //  while(1)
    {
      //  memset(buf, 0, BUFF_LEN);
        len = sizeof(clent_addr);
       
        count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count == -1)
        {
            printf("recieve data fail!\n");
            return;
        }
      //  std::cout<< "222" << buf[0]<< std::endl;
     
       struct scan_data scan_data_buf;
        memcpy(&scan_data_buf,buf,sizeof(scan_data_buf)+1);
  //     std::cout<<"scan_data_buf:   "<<scan_data_buf.frame_id;
  //      std::cout<<scan_data_buf.angle_min<<"  "<<scan_data_buf.angle_max<<"   "<<scan_data_buf.scan_time<< std::endl;
        std::cout<<scan_data_buf.ranges[0]<<"  "<<scan_data_buf.intensities[1]<< std::endl;
       // memset(buf, 0, BUFF_LEN);
       // sprintf(buf, "I have recieved %d bytes data!\n", count);  //回复client
       // printf("server:%s\n",buf);  //打印自己发送的信息给
       // sendto(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, len);  //发送信息给client，注意使用了clent_addr结构体指针

    }
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "scan_ser");
  ros::NodeHandle n;
 // ros::Subscriber sub = n.subscribe("scan", 1, scan_callback);

  /////udp//////////

    int server_fd, ret;
    struct sockaddr_in ser_addr; 

    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
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
        return -1;
    }

    handle_udp_msg(server_fd);   //处理接收到的数据

    close(server_fd);


  ros::spin();


  return 0;
}
