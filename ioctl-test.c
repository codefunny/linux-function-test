/*
    file:
    author:steven
    create:2013-3-30
    description:利用ioctl查看网络IP、mask、broadaddr

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>


void usage()
{
    printf("usage:ipconfig interface\n");
    exit(1);
}

int main(int argc,char** argv)
{
    struct sockaddr_in *addr;
    struct ifreq ifr;
    char *name,*address;
    int sockfd;

    if(argc != 2) usage();
    else name = argv[1];

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    strncpy(ifr.ifr_name,name,IFNAMSIZ-1);

    if(ioctl(sockfd,SIOCGIFADDR,&ifr) == -1)
        perror("ioctl error\n"),exit(1);

    addr = (struct sockaddr_in *)&(ifr.ifr_addr);
    address = inet_ntoa(addr->sin_addr);
    printf("inet addr:%s\n",address);

    if(ioctl(sockfd,SIOCGIFNETMASK,&ifr) == -1)
        perror("ioctl error\n"),exit(1);
    addr = (struct sockaddr_in*)&(ifr.ifr_addr);
    address = inet_ntoa(addr->sin_addr);
    printf("mask:%s\n",address);

    if(ioctl(sockfd,SIOCGIFBRDADDR,&ifr) == -1)
       perror("ioctl error\n"),exit(1);
    addr = (struct sockaddr_in*)&(ifr.ifr_broadaddr);
    address = inet_ntoa(addr->sin_addr);
    printf("broadaddr:%s\n",address);

    return 0;
}


/*==================================================
int ioctl(int fd, int request, …/*void *arg */);

    返回：成功返回0，出错返回-1；
==================================================*/
/*--------------------------------------------------------------
类别   Request           说明                          数据类型
===============================================================
套    SIOCATMARK      是否位于带外标记                 int  
                                                          
接    SIOCSPGRP       设置套接口的进程ID 或进程组ID    int
                                                          
口    SIOCGPGRP       获取套接口的进程ID 或进程组ID    int
================================================================
文    FIONBIN         设置/ 清除非阻塞I/O 标志         int
                                                          
件    FIOASYNC        设置/ 清除信号驱动异步I/O 标志   int
                                                         
      FIONREAD        获取接收缓存区中的字节数         int
                                                          
      FIOSETOWN       设置文件的进程ID 或进程组ID      int
                                                          
      FIOGETOWN       获取文件的进程ID 或进程组ID      int
==================================================================
接    SIOCGIFCONF     获取所有接口的清单           struct ifcon  
                                                               
口    SIOCSIFADDR     设置接口地址                 struct ifreq
	                                                           
      SIOCGIFADDR     获取接口地址                 struct ifreq
                                                               
      SIOCSIFFLAGS    设置接口标志                 struct ifreq
                                                               
      SIOCGIFFLAGS    获取接口标志                 struct ifreq
                                                               
      SIOCSIFDSTADDR  设置点到点地址               struct ifreq
                                                               
      SIOCGIFDSTADDR  获取点到点地址               struct ifreq
                                                               
      SIOCGIFBRDADDR  获取广播地址                 struct ifreq
                                                               
      SIOCSIFBRDADDR  设置广播地址                 struct ifreq
                                                               
      SIOCGIFNETMASK  获取子网掩码                 struct ifreq
                                                               
      SIOCSIFNETMASK  设置子网掩码                 struct ifreq
                                                               
      SIOCGIFMETRIC   获取接口的测度               struct ifreq
                                                               
      SIOCSIFMETRIC   设置接口的测度               struct ifreq
                                                               
      SIOCGIFMTU      获取接口MTU                  struct ifreq
                                                   
      SIOCxxx         （还有很多取决于系统的实现） 
================================================================
ARP   SIOCSARP        创建/ 修改ARP 表项           struct arpreq
	                                                            
      SIOCGARP        获取ARP 表项                 struct arpreq
                                                                
      SIOCDARP        删除ARP 表项                 struct arpreq
================================================================
路    SIOCADDRT       增加路径                     struct rtentry
                                                                 
由    SIOCDELRT       删除路径                     struct rtentry
------------------------------------------------------------------*/

/*--------------------------------------------------------------
struct ifreq
{
#define IFHWADDRLEN 6
 union
 {
  char ifrn_name[IFNAMSIZ];  
 } ifr_ifrn;
 
 union {
  struct sockaddr ifru_addr;
  struct sockaddr ifru_dstaddr;
  struct sockaddr ifru_broadaddr;
  struct sockaddr ifru_netmask;
  struct  sockaddr ifru_hwaddr;
  short ifru_flags;
  int ifru_ivalue;
  int ifru_mtu;
  struct  ifmap ifru_map;
  char ifru_slave[IFNAMSIZ]; 
  char ifru_newname[IFNAMSIZ];
  void __user * ifru_data;
  struct if_settings ifru_settings;
 } ifr_ifru;
};

#define ifr_name ifr_ifrn.ifrn_name 
#define ifr_hwaddr ifr_ifru.ifru_hwaddr 
#define ifr_addr ifr_ifru.ifru_addr 
#define ifr_dstaddr ifr_ifru.ifru_dstaddr 
#define ifr_broadaddr ifr_ifru.ifru_broadaddr 
#define ifr_netmask ifr_ifru.ifru_netmask 
#define ifr_flags ifr_ifru.ifru_flags 
#define ifr_metric ifr_ifru.ifru_ivalue 
#define ifr_mtu  ifr_ifru.ifru_mtu 
#define ifr_map  ifr_ifru.ifru_map 
#define ifr_slave ifr_ifru.ifru_slave 
#define ifr_data ifr_ifru.ifru_data 
#define ifr_ifindex ifr_ifru.ifru_ivalue 
#define ifr_bandwidth ifr_ifru.ifru_ivalue   
#define ifr_qlen ifr_ifru.ifru_ivalue 
#define ifr_newname ifr_ifru.ifru_newname 
#define ifr_settings ifr_ifru.ifru_settings 
----------------------------------------------------------------*/
