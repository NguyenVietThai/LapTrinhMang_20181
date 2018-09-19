#include <stdio.h>
#include "lib.h"

//Main program------------------------------------
int main(){
    head = NULL;
    int choice = 1;
    int open_file = loadData();

    //if file "account.txt" have ?
    if(open_file == 1){
        while(choice == 1 || choice == 2 || choice == 3 || choice == 4 ){
            menu();
            scanf("%d",&choice);

            switch(choice){
                case 1:  
                    Register();                                       
                    break;
                case 2:
                    Signin();
                    break;
                case 3:
                    Search_output();
                    break;
                case 4:
                    Signout();
                    break;
            }
        }
    }

    //if file not have ?
    else{
            printf("Can't run program because file 'account.txt' is LOST!\nPlease check file account have?\n\n\n");
            return 0;
        }
}