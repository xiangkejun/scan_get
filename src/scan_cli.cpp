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
     
int client_fd;
struct sockaddr_in ser_addr;

using namespace std;

#define SERVER_PORT 8888




 //void udp_msg_sender(int fd, struct sockaddr* dst)
//   void udp_msg_sender()
//  {

// //     socklen_t len;
//       while(ros::ok())
//       {
// //         printf("client:\n");  //打印自己发送的信息
// //         len = sizeof(*dst);
//    sendto(client_fd, (char *)&scan_data, sizeof(scan_data)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

// //         sendto(fd, scan_temp, 100, 0, dst, len);
// //         memset(&scan_data, 0, 100);
//    //      sleep(1);
//      }
//  }


//void *scan_get( void *arg )
void scan_send( )
{
  while(ros::ok())
// while(1)
      {
//         printf("client:\n");  //打印自己发送的信息
//         len = sizeof(*dst);
std::cout<<scan_data_buf.angle_min << scan_data_buf.angle_max<< std::endl;

  sendto(client_fd, (char *)&scan_data_buf, sizeof(scan_data_buf)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

 // sendto(client_fd, (char *)&scan_data_msg, sizeof(scan_data_msg)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

 //   cout << "cli..........."<<endl;
//         sendto(fd, scan_temp, 100, 0, dst, len);
//         memset(&scan_data, 0, 100);
        sleep(1);
     }
}
// void create_all_thread(void)
// {
// 	pthread_t thread_scan_get;
// 	if( (pthread_create( &thread_scan_get , NULL , scan_get, NULL )) != 0 )
// 	{
// 		perror("Create the thread_joy fail");
// 		exit( 1 );
// 	}
// }


int main(int argc, char **argv)
{

   ros::init(argc, argv, "scan_data_cli");
   ros::NodeHandle n;
 // ros::Subscriber sub = n.subscribe("scan", 1, scan_callback);

  /////udp//////////


    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
    ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换

  //  udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);
    // udp_msg_sender();
   // create_all_thread(); 
     scan_send();
    close(client_fd);
 //   ros::spin();
  return 0;
}