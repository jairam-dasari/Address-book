#ifndef HEADER_H
#define HEADER_H

#include "main.h"

//to create//add new contract
status create_new_contact(data *);

//to check entered name contains only letters
status valid_name(char *);

//to check entered mobile number validity
status valid_mobile_num(char *);

//to check entered email id validity
status valid_email_id(char *);

//to check entered mobile number is unique(not matched with recored list)
status unique_mobile_num(data *, char *);

//to check entered mail id is unique(not matched with recored list)
status unique_email_id(data *, char *);

//to list recorded contact list
status list_contacts(data *);

//to search contacts
no_of_contact_found search_contact(data *);

//to edit recorded contacts
status edit_contact(data *);

//to edit recorded contact name
status edit_name(int, data *);

///to edit recorded contact moblie number
status edit_mob_no(int, data *);

////to edit recorded contact email id
status edit_email_id(int, data *);

//to delete recorded contact
status delete_contact(data *);

//to select options
int select();

//to swap selected to last index
status swap_contact(data *, int);

//to save temp recorded contact to a file
void save_and_exit(data *);
#endif