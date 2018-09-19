//create struct linkList for program
typedef struct linklist{
    char username[20];
    char password[20];
    int status;         		//check active or block?
    int signin;         		//check sign in?
    int count;          		// check if password error 3 time ? ->block account
    struct linklist *next;
}node;

node *head; 					//node head of linklist

//functions of program
node* Search(char user[20]);
int Search_output(); 			//show results found
int writeData(node* data);
int resetData();
int Register();
int Signin();
int Signout();
int loadData();
int menu();

