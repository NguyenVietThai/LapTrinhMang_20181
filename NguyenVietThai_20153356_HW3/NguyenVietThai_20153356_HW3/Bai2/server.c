#include <stdio.h>    
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[]){

    int sock,recv_, send_;
    char buff[BUFF_SIZE];
    int check,sin_size;
    struct sockaddr_in server, client;

    //kiem tra tham so dau vao-------------------------------------------------------------------
    if(argc < 2)
    {
        printf("Input parameter Invalid!\n");
        return 0;
    }

    //Step 1: Construct a UDP socket-----------------------------------------------------------
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        printf("Chua tao duoc socket\n");
        return 0;
    }
    
    //Step 2: Bind address to socket------------------------------------------------------------
    server.sin_family = AF_INET;         
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server.sin_zero),8);

    check = bind(sock,(struct sockaddr *)&server, sizeof(struct sockaddr));
    if(check < 0){
        printf("Co loi trong phan check lien ket: bind()\n");
        return 0;
    }

    //Step 3: Communicate with clients----------------------------------------------------------
    while(1){
        sin_size=sizeof(struct sockaddr_in);
        recv_ = recvfrom(sock, buff,BUFF_SIZE-1, 0, (struct sockaddr *)&client,&sin_size);

        //kiem tra ket qua nhan------------------------------------
        if(recv < 0){
            printf("Co loi trong qua trinh nhan du lieu\n");
            return 0;
        }else{
            buff[recv_] = '\0';
			printf("[%s:%d]: %s", inet_ntoa(client.sin_addr), ntohs(client.sin_port), buff);
        }
        buff[strlen(buff)-1]='\0';

        //phan xu li du lieu de gui lai cho client-----------------------------------------------
        int dk;
        struct in_addr someAddr;
        struct in_addr **addr_list;
        dk = inet_aton(buff, &someAddr);
        char *name;
        if(dk != 0){
            struct in_addr ip;
            struct hostent *hp;
            if (!inet_aton(buff, &ip)) {
                fprintf(stderr, "can't parse IP address %s\n", buff);
                return 1;
            }

            hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET);
            if(hp != NULL){
                name = hp->h_name;
            }else{
                name = "Not found information";
            }        
        }else if(gethostbyname(buff) != NULL){
            struct hostent *add;
            add = gethostbyname(buff);
            addr_list = (struct in_addr **)add->h_addr_list;
            char *addr = inet_ntoa((struct in_addr) *((struct in_addr *) add->h_addr_list[0]));
            name = addr;
        }else{
            if(!inet_aton(buff, &someAddr))
                name = "IP Address is Invalid";
            if(gethostbyaddr((const void *)&someAddr, sizeof someAddr, AF_INET) == NULL)   
                name = "Not found information";
        }

        //chinh sua lai du lieu de gui cho client-------------------------------------------------
        char *name_send;
        strcpy(name_send,"Offical:  ");
        strcat(name_send,name);

        //gui du lieu ve cho client------------------------------------------------------------------------------------------
        send_= sendto(sock, name_send, BUFF_SIZE-1, 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) ); /* send to the client welcome message */
		if (send_ < 0){
            printf("Co loi trong viec gui du lieu lai client\n");	
        }
    }
    close(sock);
	return 0;
}