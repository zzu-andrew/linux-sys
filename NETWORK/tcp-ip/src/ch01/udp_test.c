//
// Created by andrew on 2020/11/29.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE  150   /* arbitrary size */

int main(int argc, char *argv[]) {

    struct sockaddr_in serv;
    char buff[BUFF_SIZE];
    int sockFd, n;

    if((sockFd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket error\n");
        return -1;
    }

    sendto()

    return 0;
}
