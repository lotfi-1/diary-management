//
// Created by lotfihallas on 2/28/22.
//

#ifndef UNTITLED_MANAGEMENT_H
#define UNTITLED_MANAGEMENT_H


typedef struct date date ;
struct date {
    char year[5];
    char month[3];
    char day[3];
};
typedef struct record record ;
struct record{
    char name[15];
    char place[20];
    char not[2048];
};

typedef struct password password;
struct password{
    char first_name[11];
    char discrib[11];
    char date_of_birth[12] ;
    char pass[20];
};
void diary_management_create();
bool date_(char *data);
void add_record();
bool check_pass(char *user,char *pass);
void close();
char *user_interface();
void edit_record();
int view_existing_record(char *file);
void view_record();
void remove_record();
void edit_password(char *file);
void menu();
void birthday(char *file,char *date_today);
#endif //UNTITLED_MANAGEMENT_H
