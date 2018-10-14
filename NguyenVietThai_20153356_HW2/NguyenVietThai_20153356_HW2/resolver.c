/*
Name    :   Nguyen Viet Thai
MSSV    :   20153356
Created at 26/9/2018
*/

#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

    int dk;
    struct in_addr someAddr;
    struct in_addr **addr_list;

    //iNPUT - check IP and domain name
    char *info = argv[1];
    if(argc < 2){
        printf("Not have IP address or Domain name? Try again");
        return 0;
    }
        
    printf("INPUT   : %s\n",info);
    dk = inet_aton(info, &someAddr);

    //OUTPUT
    printf("--------------------------------\nOUTPUT  : \n");

    // IP address ---------------------------------------------------------
    if(dk != 0){
        struct in_addr ip;
        struct hostent *hp;

        if (argc != 2) {
            fprintf(stderr, "usage: %s ipaddr\n", argv[0]);
            return 1;
        }

        if (!inet_aton(argv[1], &ip)) {
            fprintf(stderr, "can't parse IP address %s\n", argv[1]);
            return 1;
        }

        if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
            printf("Not found information\n");
            return 1;
        }
        printf("Official IP :%s\n",hp->h_name);
        printf("Alias name:");
        addr_list = (struct in_addr **)hp->h_aliases;
        if(addr_list[0] != NULL){
            for(int i = 0; addr_list[i] != NULL; i++) {
                printf("\n%s ", inet_ntoa(*addr_list[i]));
            }
        }
        printf("\n");
        
        return 0;

    }

    //Domain name --------------------------------------------------------------
    else if(gethostbyname(info) != NULL){
        
        struct hostent *add;
        add = gethostbyname(info);
        //printf("%s",add->h_name);
        addr_list = (struct in_addr **)add->h_addr_list;
        char *addr = inet_ntoa((struct in_addr) *((struct in_addr *) add->h_addr_list[0]));
        printf("\nOfficial IP : %s\n",addr);
        printf("Alias IP:\n");
        for(int i = 1; addr_list[i] != NULL; i++) {
            printf("\n%s ", inet_ntoa(*addr_list[i]));
        }
        printf("\n");
        return 1;
    }

    // Not information ------------------------------------------------------------
    printf("Not found information\n");
    return 0;
}

