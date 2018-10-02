#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>



#define SERVER_PORT 8888
#define BUFF_LEN 512

  int client_fd;
    struct sockaddr_in ser_addr;

struct udp
{
char msg[50];
int num;
double socre;
};




// void udp_msg_sender(int fd, struct sockaddr* dst)
// {

//     socklen_t len;
//     struct sockaddr_in src;
//     while(1)
//     {
//         udp udp_buf={"Hello everybody!",1,1.2};

//         // char buf[BUFF_LEN] = "TEST UDP MSG!\n";
//          len = sizeof(*dst);
//         // printf("client:%s\n",buf);  //打印自己发送的信息
//         // sendto(fd, buf, BUFF_LEN, 0, dst, len);
//          sendto(fd, (char *)&udp_buf, sizeof(udp_buf)+1, 0, dst, len);

//         // memset(buf, 0, BUFF_LEN);
//         // recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
//         // printf("server:%s\n",buf);
//         // sleep(1);  //一秒发送一次消息
//     }
// }



void udp_msg_sender()
{

  
    while(1)
    {
        udp udp_buf={"Hello everybody!",1,1.2};

        // char buf[BUFF_LEN] = "TEST UDP MSG!\n";
       //  len = sizeof(*dst);
        // printf("client:%s\n",buf);  //打印自己发送的信息
        // sendto(fd, buf, BUFF_LEN, 0, dst, len);
      //   sendto(fd, (char *)&udp_buf, sizeof(udp_buf)+1, 0, dst, len);
    sendto(client_fd, (char *)&udp_buf, sizeof(udp_buf)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

        // memset(buf, 0, BUFF_LEN);
        // recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
        // printf("server:%s\n",buf);
         sleep(1);  //一秒发送一次消息
    }
}
/*
    client:
            socket-->sendto-->revcfrom-->close
*/

int main(int argc, char* argv[])
{
  

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

    udp_msg_sender();

    close(client_fd);

    return 0;
}
