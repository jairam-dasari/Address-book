#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include "definition.h"
#include "main.h"


extern int count;
extern int pos[100];


status create_new_contact(data *member){
        printf("ENTER NAME: ");
        while (1)
        {
            scanf("%[^\n]",member[count].name);
            while (getchar() != '\n');
            int val_name=valid_name(member[count].name);
            if (val_name==1)         //to check enterd name valid(only charcters)
            {
            break;
            }
            else
            printf("ENTER PROPER NAME...!!!\n");
        }
        printf("ENTER MOBILE NUMBER: ");
        while (1)
        {
            scanf("%s",member[count].mobile_no);
            while (getchar() != '\n');
            status val_mob_num=valid_mobile_num(member[count].mobile_no);
            status unique_mob_num=unique_mobile_num(member,member[count].mobile_no);
            if (val_mob_num&&unique_mob_num)   //to check entered moblie number is unique(compare with recored contacts) and valid(10 digit number)
            {
                break;
            } 
        }
        printf("ENTER EMAIL ID: ");
        while (1)
        {
            scanf("%s", member[count].email_id);
            while (getchar() != '\n');
            status val_email_id = valid_email_id(member[count].email_id);
            status uni_email_id = unique_email_id(member,member[count].email_id);
            if (val_email_id && uni_email_id)   //to check entered mail id is unique(compare with recored contacts) and valid(lower case,contain @,contains .com at last)
            {
                break;
            }
        }
        member[count].serial_no = count + 1;  //to add serial number
        count++;
        printf("NEW CONTACT SUCCESSFULLY ADDED...!!!\n");
}


no_of_contact_found search_contact(data *data_base){
    if (count == 0)
    {
        printf("THERE ARE NO SAVED CONTACTS..!!!!\n");
        return -1;
    }
    int choice = select();             //select options name/moblie num/mail id
    no_of_contact_found found = 0;
    switch (choice)
    {
    case e_name:
        printf("ENTER NAME: ");
        while (1)
        {
            scanf("%[^\n]",data_base[count].name);
            while (getchar() != '\n');
            int val_name = valid_name(data_base[count].name);
            if (val_name == 1)
            {
            break;
            }
            else
            printf("ENTER PROPER NAME...!!!\n");
        }
        for (int i = 0; i < count; i++)
        {
            if (strcmp(data_base[i].name, data_base[count].name) == 0)
            {
                pos[found++] = i;
            }
            
        }
        break;
    case e_mobile_number:
        printf("ENTER MOBILE NUMBER: ");
        while (1)
        {
            scanf("%s", data_base[count].mobile_no);
            while (getchar() != '\n');
            status val_mob_num = valid_mobile_num(data_base[count].mobile_no);
            if (val_mob_num)
            {
                break;
            } 
        }
        for (int i = 0; i < count; i++)
        {
            if (strcmp(data_base[i].mobile_no,data_base[count].mobile_no) == 0)     //compare moblie number with recored mobile number
            {
                pos[found++] = i;
            }
            
        }
        break;
    case e_email_id:
        printf("ENTER EMAIL ID: ");
        while (1)
        {
            scanf("%s",data_base[count].email_id);
            while (getchar() != '\n');
            status val_email_id = valid_email_id(data_base[count].email_id);
            if (val_email_id)
            {
                break;
            }
        }
        for (int i = 0; i < count; i++)
        {
            if (strcmp(data_base[i].email_id,data_base[count].email_id) == 0)
            {
                pos[found++] = i;
            }
            
        }
        break;
    default:
        printf("hi how are you\n");
        break;
    }
    if (found > 0)
    {
        printf("CONTACTS FOUND : \n");
        printf("-------------------------------------------------------------------------------\n");
        printf("S_NO\tNAME\t\tMOBILE NUMBER\tEMAIL ID\n");
        printf("-------------------------------------------------------------------------------\n");
        for (int i = 0; i < found; i++)
        {
            printf("%-10d%-20s%-15s%-30s\n", data_base[pos[i]].serial_no, data_base[pos[i]].name, data_base[pos[i]].mobile_no, data_base[pos[i]].email_id);
        }
        printf("-------------------------------------------------------------------------------\n");   
    }
    else
    printf("NO MATCHED CONTACTS FOUND WITH ENTERED DETAILS..!!!\n");
    return found; 
}


status edit_contact(data *data_base){
    no_of_contact_found found;
    if (count == 0)
    {
        printf("NO CONTACTS TO EDIT...!!!\n");
        return 0;
    }
    search_again:
    found = search_contact(data_base);
    if (found <= 0)
    {
        return -1;
    }
    else if (found == 1)
    {
        int choice;
        serial:
        choice = select();
        switch (choice)
        {
        case e_name:
            edit_name(pos[0],data_base);
            break;
        case e_mobile_number:
            edit_mob_no(pos[0],data_base);
            break;
        case e_email_id:
            edit_email_id(pos[0],data_base);
            break;
        default:
            break;
        }
    }
    else         //in case of more than 1 contacts are found we can edit using serial number or we can search again
    {
    printf("MORE THAN ONE MATCH FOUND...!!!\n");
    short int choice = 0;
    printf("1.EDIT BY SERIAL NUMBER\n2.SEARCH AGAIN\n3.RETURN TO MENU\n");
    while (1)
    {
        scanf("%hd", &choice);
        while (getchar() != '\n');
        if (choice >= 1 && choice <= 3)
        {
            break;
        }
        else
        printf("select proper choice...!!! \n");
    }
    switch (choice)
    {
    case 1:
        printf("ENTER SERIAL NUMBER: ");
        while (1)
        {
            scanf("%d",&pos[0]);
            while (getchar() != '\n');
            if (pos[0] <= count && pos[0] > 0)
            {
                pos[0] = pos[0] - 1;         
                goto serial;
            }
            else
            printf("ENTER PROPER SERIAL NUMBER...!!!\n"); 
        }
        break;
    case 2:
        goto search_again;
    case 3:
    return -1;
    }
    }
    
}


status delete_contact(data *data_base){
    no_of_contact_found found;
    int serial, temp = 0;
    search_again:
    found = search_contact(data_base);        //to search which contact we want to delete
    if (found <= 0)
    {
        printf("1.search again\n2.return to main menu\n");
        while (temp == 1 || temp == 2)
        {
            scanf("%d", &temp);
            while (getchar() != '\n');     //to clear input buffer
        }
        return -1;
    }
    else if (found == 1)
    {
       swap_contact(data_base,pos[0]);
       printf("contact delete sucessfully...!!!\n");
       return 1;
    }
    else              //if we found more than 1 contact with entered details either delete by serial number or search again 
    {
    printf("MORE THAN ONE MATCH FOUND...!!!\n");
    short int choice = 0;
    printf("1.EDIT BY SERIAL NUMBER\n2.SEARCH AGAIN\n3.RETURN TO MENU\n");
    while (1)
    {
        scanf("%hd", &choice);
        while (getchar() != '\n');
        if (choice >= 1&&choice <= 3)
        {
            break;
        }
        else
        printf("select proper choice...!!! \n");
    }
    switch (choice)
    {
    case 1:
        printf("ENTER SERIAL NUMBER: ");
        while (1)
        {
            scanf("%d", &serial);
            while (getchar() != '\n');
            if (serial <= count && serial>0)
            {
                swap_contact(data_base, serial-1);       //to swap contact to last which we want to delte
                printf("contact delete sucessfully...!!!\n");
                break;
            }
            else
            printf("ENTER PROPER SERIAL NUMBER...!!!\n"); 
        }
        break;
    case 2:
        goto search_again;
    case 3:
    return -1;
    }
    }
}


status list_contacts(data *data_base){
    if (count == 0)
    {
        printf("NO CONTACTS TO DISPLAY...!!!\n");
        return 0;
    }
    
    printf("-------------------------------------------------------------------------------\n");
    printf("%-10s%-20s%-15s%-30s\n","S_NO","NAME","MOBILE NUMBER","EMAIL ID");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)        //to print all recorded contacts
    {
        printf("%-10d%-20s%-15s%-30s\n", data_base[i].serial_no, data_base[i].name, data_base[i].mobile_no, data_base[i].email_id);
    }
    printf("-------------------------------------------------------------------------------\n");
}


status valid_name(char *name){
    while (*name != '\0')
    {
        if (isalpha(*name) == 0)         //to check all are only letters
        {
            printf("ENTER ONLY ALPHABETS....!!!\n");
            return e_failure;
        }
        name++;
    }
    return e_success;
}


status valid_mobile_num(char *number){
    if (strlen(number) != 10)            //to check it contains exctaly 10 digits or not
    {
        printf("ENTER 10 DIGITS..!!!!!\n");
        return e_failure;
    }
    
    while (*number != '\0')
    {
        if (isalnum(*number) == 0)          //to check all 10 character are digits
        {
            return e_failure;
        }
        number++;
    }
    return e_success;
}


status unique_mobile_num(data *data_base, char *number){
    for (int i = 0; i < count; i++)
    {
        if (strcmp(data_base[i].mobile_no,number) == 0)   //compare with recored moblie number
        {
            printf("ENTERED NUMBER IS ALREADY EXISTED....!!!\n");
            return e_failure;
        }
    }
    return e_success;
}


status valid_email_id(char *email_id){
    int length=strlen(email_id);
    char *at_the_rate=strchr(email_id,'@');       //to check it contains '@'
    if (at_the_rate == NULL)
    {
        printf("ENTER PROPER EMAIL ID....!!!");
        return e_failure;
    }
    if (isalpha(*(at_the_rate - 1)) == 0 && isalnum(*(at_the_rate - 1)) == 0)    //to check '@' before character is not a digit
    {
        printf("ENTER PROPER EMAIL ID.!!!!");
        return e_failure;
    }
    if (isalpha(*(at_the_rate + 1)) == 0 && isalnum(*(at_the_rate + 1)) == 0)      //to check '@' after character is not a digit
    {
        printf("ENTER PROPER EMAIL ID.!!!!");
        return e_failure;
    }
    if (strcmp((email_id + length - 4),".com") != 0)          //to last 4 character are ".com"
    {
        printf("ENTER PROPER EMAIL ID.!!!!");
        return e_failure;
    }
    return e_success;
}


status unique_email_id(data *data_base, char *email_id){
    for (int i = 0; i < count; i++)
    {
        if (strcmp(data_base[i].email_id,email_id) == 0)       //compare with recored email id
        {
            printf("ENTERED EMAIL ID IS ALREADY EXISTS...!!!\n");
            return e_failure;
        }
    }
    return e_success;
}


int select(){
    int choice = 0;
    printf("1.NAME\n2.MOBILE NUMBER\n3.EMAIL ID\n");
    while (1)
    {
        scanf("%d", &choice);
        while (getchar() != '\n');
        if (choice >= 1&&choice <= 3)
        {
            break;
        }
        else
        printf("select proper choice...!!! ");
    }
    return choice;
}


status edit_name(int pos, data *database){
    printf("ENTER NAME: ");
        while (1)
        {
            scanf("%[^\n]", database[count].name);
            while (getchar() != '\n');
            int val_name = valid_name(database[count].name);
            if (val_name == 1)
            {
            break;
            }
            else
            printf("ENTER PROPER NAME...!!!\n");
        }
        strcpy(database[pos].name, database[count].name);   //change name
}


status edit_mob_no(int pos, data *database){
    printf("ENTER MOBILE NUMBER: ");
        while (1)
        {
            scanf("%s", database[count].mobile_no);
            while (getchar() != '\n');
            status val_mob_num = valid_mobile_num(database[count].mobile_no);
            status unique_mob_num = unique_mobile_num(database,database[count].mobile_no);
            if (val_mob_num && unique_mob_num)
            {
                break;
            } 
        }
        strcpy(database[pos].mobile_no, database[count].mobile_no);  //change moblie number
}


status edit_email_id(int pos, data *data_base){
    printf("ENTER EMAIL ID: ");
        while (1)
        {
            scanf("%s", data_base[count].email_id);
            while (getchar() != '\n');
            status val_email_id = valid_email_id(data_base[count].email_id);
            status uni_email_id = unique_email_id(data_base,data_base[count].email_id);
            if (val_email_id && uni_email_id)
            {
                break;
            }
        }
        strcpy(data_base[pos].email_id, data_base[count].email_id);     //change email id
}


status swap_contact(data *data_base, int pos){
    int serial = data_base[pos].serial_no;
    data_base[pos] = data_base[--count];
    data_base[pos].serial_no = serial;
}


void save_and_exit(data *data_base){
    FILE *fp=fopen(FILE_NAME, "w");       //to write count of recored contacts in first line of file
    fprintf(fp, "#%d,\n", count);
    for (int i = 0; i <count; i++)
    {
        fprintf(fp,"%d,%s,%s,%s,\n", data_base[i].serial_no, data_base[i].name, data_base[i].mobile_no, data_base[i].email_id);
    }
    fclose(fp);
}