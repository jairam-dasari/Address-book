#ifndef E_NUM_H
#define E_NUM_H

#define FILE_NAME "data_base.csv"
typedef int no_of_contact_found;

typedef struct data
{
    int serial_no;
    char name[20];
    char mobile_no[11];
    char email_id[30];
}data;

typedef enum{
    e_failure,
    e_success
}status;

typedef enum{
    e_default,
    e_name,
    e_mobile_number,
    e_email_id
}by;

enum{
    create_contact=1,
    search,
    edit,
    delete,
    display,
    save
};

#endif