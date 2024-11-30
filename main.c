#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "definition.h"
#include "main.h"


int count;
int pos[100];


int main(){
    int choice;
    struct data dat[100];
    char str[100];
    FILE *fp=fopen(FILE_NAME,"r");       //file erroer check
    if (fp==NULL)
    {
        fp=fopen(FILE_NAME,"w");         //if file is deleted or incase of begining creared new file
        fprintf(fp,"#0,\n");          
    }
    fclose(fp);

    fp=fopen(FILE_NAME,"r");       //open data base file in read mode
    fgets(str,10,fp);
    count=atoi(str+1);
    for (int i = 0; i < count; i++)   //read all stored contacted into structure array for file
    {
        fgets(str,50,fp);
        dat[i].serial_no=atoi(strtok(str,","));
        strcpy(dat[i].name,strtok(NULL,","));
        strcpy(dat[i].mobile_no,strtok(NULL,","));
        strcpy(dat[i].email_id,strtok(NULL,","));
    }
    fclose(fp);
    do
    {
        printf("1.CREATE NEW CONTACT\n2.SEARCH CONTACT\n3.EDIT CONTACT\n4.DELETE CONTACT\n5.LIST CONTACTS\n6.SAVE&EXIT\n");
        printf("ENTER YOUR CHOICE(1to6): ");
        while (1)
        {
            choice=0;
            scanf("%d",&choice);      //readind choice for user
            while (getchar()!='\n');
            if (choice>=1&&choice<=6){
                break;
            }
            else
            printf("please enter number between 1 to 6...!!!: \n");
        }
        switch (choice)
        {
        case create_contact:
            create_new_contact(dat);
            break;
        case search:
            search_contact(dat);
            break;
        case edit:
            edit_contact(dat);
            break;
        case delete:
            delete_contact(dat);
            break;
        case display:
            list_contacts(dat);
            break;
        case save:
            save_and_exit(dat);
            break;
        default:
            printf("just for fun\n");
            break;
        }
    } while (choice != 6);      //loop run until user choose to 6th option save and exit
    return 0;
}
