#include <stdio.h>    
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFF_SIZE 1024      //kich thuoc buffer

//kiem tra mot chuoi nhap vao xem co ki tu khong hop le hay khong--------------------------
int check_string_error(char *buff){
    for(int i =0 ;i<strlen(buff);i++){
        if(isdigit(buff[i]) == 0 && isalpha(buff[i]) == 0)
            return 1;   //co ki tu khong hop le
    }
    return 0;           //chuoi chi chua chu cai va chu so
}

int main(int argc, char *argv[]){

    int sock,recv_, send_;
    char buff[BUFF_SIZE];
    int check,sin_size;
    struct sockaddr_in server, client;

    //Check input parameter------------------------------------------------------------------
    if(argc != 2)
    {
        printf("Form Invalid!\n");      //cau truc nhap lieu khong chinh xac
        return 0;
    }

    //Step 1: Construct a UDP socket---------------------------------------------------------
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        printf("Chua tao duoc socket\n");
        return 0;
    }
    
    //Step 2: Bind address to socket-----------------------------------------------------------
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

        //kiem tra ket qua nhan------------------------------------------
        if(recv < 0){
            printf("Co loi trong qua trinh nhan du lieu\n");
            return 0;
        }else{
            buff[recv_] = '\0';
			printf("[%s:%d]: %s", inet_ntoa(client.sin_addr), ntohs(client.sin_port), buff);
        }
 
        //Phan xu li du lieu de gui lai cho client--------------------------------------------------

        char name[BUFF_SIZE];
        buff[strlen(buff)-1]='\0';
        int dk = check_string_error(buff);
        if(dk == 1){
            strcpy(name,"Error");
        }else{
            
            int x = 0;
            char name_so[BUFF_SIZE];
            for(int i=0;i<strlen(buff);i++){
                if(isdigit(buff[i]) != 0 )
                    {
                        name_so[x] = buff[i];
                        x++;
                    }   
            }
            name_so[x]='\0';

            int y = 0;
            char name_chu[BUFF_SIZE];
            for(int i=0;i<strlen(buff);i++){
                if(isalpha(buff[i]) != 0 )
                    {
                        name_chu[y] = buff[i];
                        y++;
                    }   
            }
            name_chu[y]='\0';

            strcpy(name,name_so);
            strcat(name," \n");
            strcat(name,name_chu);

        }
        
        //gui du lieu ve cho client-------------------------------------------------------------------------
        send_= sendto(sock, name_send, BUFF_SIZE-1, 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) );
		if (send_ < 0){
            printf("Co loi trong viec gui du lieu lai client\n");	
        }
        
    }
    close(sock);
	return 0;
}