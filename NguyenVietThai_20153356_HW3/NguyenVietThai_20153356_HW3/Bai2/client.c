#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define BUFF_SIZE 1024

int main(int argc , char *argv[]){

    int sock_c,recv_,send_,sin_size;
    struct sockaddr_in server;
    struct hostent *hp;
    char buff[BUFF_SIZE];

    //check du lieu nhap vao-------------------------------------------------------------
    if(argc != 3){
        printf("Cu phap nhap vao khong chinh xac\n");
        return 0;
    }

    //Step 1: Construct a UDP socket-----------------------------------------------------
    sock_c = socket(AF_INET, SOCK_DGRAM,0);
    if(sock_c < 0){
        printf("Khoi tao socket bi loi\n");
        return 0;
    }

    //Step 2: Define the address of the server--------------------------------------------
    bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if(hp == 0){
        printf("Khong tim thay thong tin ve dia chi: %s\n",argv[1]);
        return 0;
    }
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    //Step 3: Communicate with server---------------------------------------------------
    while(1){
        printf("\n\n------------------\nINPUT :   ");
        memset(buff,'\0',(strlen(buff)+1));
        fgets(buff, BUFF_SIZE, stdin);
        //printf("[%s]\n",buff);
        if(strcmp(buff,"\n") == 0){
            printf("GOOD BYE!\n");
            close(sock_c);
            return 0;
        }
        sin_size = sizeof(struct sockaddr);
        send_ = sendto(sock_c, buff, strlen(buff), 0, (struct sockaddr *) &server, sin_size);
        if(send_ == -1){
            printf("Co loi trong qua trinh gui du lieu cho server\n");
            close(sock_c);
            return 0;
        }

        recv_ = recvfrom(sock_c, buff, BUFF_SIZE - 1, 0, (struct sockaddr *) &server, &sin_size);
        if(recv_ == -1){
            printf("Co loi trong qua trinh nhan du lieu tu server\n");
            close(sock_c);
            return 0;
        }
        buff[recv_] = '\0';

        //in ket qua nhan duoc tu server---------------------------------------------------------
        printf("OUTPUT:\n");  
        printf("%s",buff);
              
    }
    close(sock_c);
    return 0;
}