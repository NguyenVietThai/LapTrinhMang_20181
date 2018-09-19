#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

//Search-------------------------------------------------------------------------------------
node* Search(char user[20]){
    node *cur = (node*)malloc(sizeof(node));
    cur = head;
    if(head == NULL){
        return NULL;
    }
    while(strcmp(cur->username,user) != 0){
        if(cur->next == NULL)
            return NULL;
        else
            cur = cur->next;
    }
    return cur;
}

//Show results found---------------------------------------------------------------------------
int Search_output(){
    char user[20];
    printf("Username:   ");scanf("%s",user);
    node *cur = Search(user);
    if(cur != NULL){
        if(cur->status == 1)
            printf("\nAccount is active");
        else printf("\nAccount is blocked");
    }else printf("\nCannot find account\n");
    return 0;
}

//write data to file "account.txt"-------------------------------------------------------------
int writeData(node* data){
    FILE *fw;
    fw = fopen("account.txt","a");
    fprintf(fw,"\n%s %s %d",data->username,data->password,data->status);
    fclose(fw);
    return 1;
}

//resetData-----------------------------------------------------------------------------------
int resetData(){
    FILE *fr;
    fr = fopen("account.txt","w");
    node* data =head;
    while(data != NULL){
        fprintf(fr,"\n%s %s %d",data->username,data->password,data->status);
        data = data->next;
    }
    fclose(fr);
    return 1;
}

//Register------------------------------------------------------------------------------------
int Register(){
    char user[20];
    char pass[20];
    printf("Username:   ");scanf("%s",user);
    node *cur = Search(user);
    if(cur != NULL){
        printf("\nAccount existed\n");
        return 0;
    }    
    else if(cur == NULL){
        printf("Password:   ");scanf("%s",pass); 
        node *new = (node*)malloc(sizeof(node));
        strcpy(new->username,user);
        strcpy(new->password,pass);
        new->status = 1;
        new->signin = 0; //now,user not sign in
        new->next = head;
        head = new;
        writeData(head);
        printf("\nSuccessful registration\n");
        return 1;
    }

}

//Sign in--------------------------------------------------------------------------------------
int Signin(){
    char user[20];
    char pass[20];
    printf("Username:   ");scanf("%s",user);
    node* cur = Search(user);
    if(cur == NULL){
        printf("\nCannot find account");
        return -1;
    }else if(cur != NULL){
        if(cur->status == 0){
                printf("\nAccount is blocked.");
                return 0;
            }   
        printf("Password:   ");scanf("%s",pass);
        if(strcmp(cur->password,pass)!=0){
            cur->count++;
            if(cur->count <3){
                printf("\nPassword is incorrect");
            }               
            else{
                cur->status = 0;
                printf("\nPassword is incorrect . Account is blocked");
            }
            resetData();
            return 0;
        }else if(strcmp(cur->password,pass)==0){
            if(cur->status == 1){
                 printf("\nHello %s",cur->username);
                 cur->signin = 1;
                 cur->count = 0; //reset count = 0 if password corrected
            }              
            return 1;
        }
    }
}

//Sign out---------------------------------------------------------------------------------------
int Signout(){
    char user[20];
    printf("Username:   ");scanf("%s",user);
    node *cur = Search(user);
    if(cur == NULL){
        printf("\nCannot find account");
        return -1;
    }else if(cur != NULL){
        if(cur->signin == 0){
            printf("\nAccount is not sign in");
            return 0;
        }else{
            cur->signin = 0;
            printf("\nGoodbye %s",cur->username);
            return 0;
        }
    }
}

//load data from file "account.txt"---------------------------------------------------------------
int loadData(){
    FILE *f;
    char user[20],pass[20];
    int act;
    f=fopen("account.txt","r");
    if(f == NULL){
        printf("\n----ERROR----\n");
        return 0; //open file error
    }
    while(1){
        fscanf(f,"%s %s %d",user,pass,&act);
        if( feof(f) ){ 
            break ;
        }
        node *new = (node*)malloc(sizeof(node));
        strcpy(new->username,user);
        strcpy(new->password,pass);
        new->status = act;
        new->signin = 0; //Not sign in
        new->next = head;
        head = new;
    }
    fclose(f);
    return 1; //open file successfully
}

//MENU USER MANAGEMENT PROGRAM----------------------------------------------------------------------
int menu(){
    printf("\n\nUSER MANAGEMENT PROGRAM \n");
    printf("-----------------------------------------------\n");
    printf("    1. Register\n");
    printf("    2. Sign in\n");
    printf("    3. Search\n");
    printf("    4. Sign out\n");
    printf("Your choice (1-4, other to quit):");
    return 0;
}

//THE END-------------------------------------------------------------------------------------------