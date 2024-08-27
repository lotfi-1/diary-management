#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include"somthing.h"
void diary_management_create(){
    char confirm[20];
    int a;
    printf("*****************************\n");
    printf("{ welcome to best diary management }\n");
    printf("*****************************\n");
    password owner ;
    password *owner_=&owner;
    printf("\n\n     Name : ");
    fgets(owner.first_name,11,stdin);
    do {
        printf("\n     Date of Birth [yyyy:mm:dd] : ");
        fgets(owner.date_of_birth, 12, stdin);
    }while(date_(owner.date_of_birth)== false);

    printf("\n     What did they call you when you were younger ?: ");
    fgets(owner.discrib,11,stdin);

    do {
        printf("\n     Password (8 character) : ");
        fgets(owner.pass, 20, stdin);
        printf("\n     Confirme Password :");
        fgets(confirm, 20, stdin);
        a=strcmp(owner.pass,confirm);
    }while(  a != 0  && strlen(owner.pass)>=8);

    FILE  *p=NULL;
    char file[16] ;
    strncpy(file,owner.first_name,strlen(owner.first_name));
    strcat(file,".bin");
    p= fopen(file,"wb");
    if(p==NULL){
        printf("Error to save thise information");
        exit(EXIT_FAILURE);
    }
    else{
        fwrite(owner_,sizeof(owner),1,p);
        printf("\n\n   Your information has been saved successfully :)    ");
    }
    fclose(p);
    close();
}
bool date_(char *data) {
    int year, month, day;
    char *end;
    year = strtod(data, &end);
    if (year < 1950 || year > 2024)
        return false;

    end++;
    month = strtod(end, &end);
    if (month < 1 || month > 12)
        return false;

    end++;
    day = strtod(end, NULL);
    if ((day < 0 || day > 31) || (month == 2 && day > 29))
        return false;

    return true;
}
void add_record() {
    struct tm *time_data;
    time_t time_1;
    time_t calender = time(&time_1);
    time_data = localtime(&calender);
    date date_1; 
    char info_date[12];
    sprintf(date_1.year,"%d",time_data->tm_year+1900);
    sprintf(date_1.month,"%d",time_data->tm_mon+1);
    sprintf(date_1.day,"%d",time_data->tm_mday);
    strncpy(info_date,date_1.year,4);
    info_date[4]=':';
    strncat(info_date,date_1.month,strlen(date_1.month));
    strcat(info_date,":");
    strncat(info_date,date_1.day,strlen(date_1.day));
    strcat(info_date,"\0");

    char file[20];
            strcpy(file,user_interface()); 
            birthday(file,info_date);
            record record_;
            FILE *pfile = NULL;
            pfile = fopen(file, "rb+");
            if (pfile == NULL) {
                printf("Error to open your diary ,try again later :( ");
                close();
            } else {
                fseek(pfile,0,SEEK_END);
                int eof=ftell(pfile);
                rewind(pfile);
                int test=1 ; 
                char daate1[12];
                fseek(pfile,54, SEEK_SET);
                while( ftell(pfile)!=eof && test!=0 ) {
                    fread(daate1,1,12,pfile);
                    test=strncmp(info_date,daate1,strlen(daate1)); 
                    if(test != 0){
                        fseek(pfile,2083,SEEK_CUR);
                    }
                }
                if(test==0){
                    printf("\n\n   This record is alredy existe , chose the \"Edit record\" option");
                    close();
                }else{
                        printf("  1- Enter the name of record : ");
                        fgets(record_.name, 15, stdin);
                        printf("  2- Enter the place : ");
                        fgets(record_.place,20, stdin);
                        printf("  3-Enter the NOTE : ");
                        fgets(record_.not,2048,stdin);
                        printf("%s\n",info_date);
                        fwrite(info_date,1,sizeof(info_date),pfile);
                        fwrite(&record_,sizeof(record_),1,pfile);
                        printf("\n      Your record has been saved successfully :) ");
                        printf("\n\n                        GOOD NIGHT :)  ");
                        fclose(pfile);
                }
            }
    close();
}
bool check_pass(char *user,char *pass){
    FILE *pfile=NULL;
    char pass_[20];
    pfile = fopen(user ,"rb" );
    if(pfile == NULL){
        printf("\nYou must create a diary firstly");
        close();
    }
    else{
        fseek(pfile,34,SEEK_SET);
        fread(pass_,1,20,pfile);
        int i ;
        i = strcmp(pass,pass_);
        fclose(pfile);
        if(i==0)
            return true ;
        else
            return false ;
    }
}
void close(){
    bool answer;
    printf("   \n\n Enter {1} to return to the menu  and  0 to exit : ");
    scanf("%d", &answer);
    if (answer == true)
    {
        menu();
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}
char *user_interface() {
    char name[15];
    char *name_=name ;
    char pass[20];
    printf("\n\n                User informations ");
    printf("\n\n    Enter your name : ");
    fgets(name,11, stdin);
    int count = 0;
    strcat(name,".bin");
    bool t_or_f;
    while (count < 3) {
        printf("\n\n    Enter your password : ");
        fgets(pass, 20, stdin);
        t_or_f = check_pass(name, pass);
        if (t_or_f == false) {
            printf("\n   Login failed , Try again ! ");
            count++;
        } else
            break;
    }
    if (count > 2) {
        char ask;
        printf("\n\n\n      *FORGET YOUR PASSWORD ? (y/n) ");
        ask = fgetc(stdin);
        if(ask=='y'){
            edit_password(name);
        }else{
        close();
        }
    } else {
        return name_ ;
    }
}
int view_existing_record(char *file){
    char user_date[12];
    FILE *pfile =NULL ;
    pfile = fopen(file,"rb");
    if(pfile==NULL){
        printf("\nError to open your diary");
        close();
    }else{
        printf("\n         VIEW RECORD     \n");
        do {
        printf("\n  * Enter the day you want : ");
        fgets(user_date,sizeof(user_date), stdin);
        }while(date_(user_date)==false);
        strcat(user_date,"\0");
        fseek(pfile,0,SEEK_END);
        int position=ftell(pfile);
        rewind(pfile);
        int test=1 ; 
        char f_date1[12];
        fseek(pfile, 54, SEEK_SET);
        while(ftell(pfile) !=position && test!=0) {
            fread(f_date1,1,12,pfile);

            test=strncmp(user_date,f_date1,strlen(f_date1)); 
            printf("%s\n%s",user_date,f_date1);
            printf("%d",test);
            if(test != 0){
                fseek(pfile,2083,SEEK_CUR);
            }
        }
        if(test==0){
            test=ftell(pfile);
            fclose(pfile);
            return test ; 
        }else{
            fclose(pfile);
            printf("  Thise record does not existe :( !!"); 
            return 0;
        }
    }
}
void edit_record(){
    char file[20] ; 
    int pos_ ; 
    strcpy(file,user_interface()); 
    FILE *pfile=NULL ; 
    pfile = fopen(file,"rb+");
    if(pfile== NULL){
        printf("\n    This diary does not existe");
        close();
    }
    else{
        char choice[2];
        record record_1,record_2;
        pos_ =view_existing_record(file); 
        if(pos_!=0){
            fseek(pfile,pos_,SEEK_SET); 
            
            printf("\n 1- Edit name of existing record ");
            printf("\n 2- Edit the location of the event ");
            printf("\n 3- Edit the note you saved ");  
            printf("\n     Chose you option : "); 
            fgets(choice,2,stdin);
            if(choice[0] =='1'){
                system("clear");
                fgetc(stdin);    
                    printf("\n  ** Enter the new name : ");
                    fgets(record_2.name,15,stdin);
                    strcat(record_2.name,"\0");
                    //fseek(pfile,-15,SEEK_CUR);
                    fwrite(&record_2.name,1,15,pfile);
                        fclose(pfile);
                        printf("\n  change the name has been success :) ");
                        close();
            }else if(choice[0]=='2'){
                system("clear");
                fgetc(stdin);
                fseek(pfile,15,SEEK_CUR);
                    printf("  Enter the new place : ");
                    fgets(record_2.place,20,stdin);
                    fwrite(&record_2.place,1,20,pfile);
                     fclose(pfile);
                        printf("\n  change the place has been success :) ");
                        close();
            }else if(choice[0]=='3'){
            system("clear");
               fgetc(stdin);
            fseek(pfile,35,SEEK_CUR);
                fread(&record_1.not,1,2048,pfile);
                strcat(record_1.not,"\0");
                  fseek(pfile,-2048,SEEK_CUR);
                int def=2048-strlen(record_1.not);
                printf("  Add note : ");
                fgets(record_2.not,def,stdin);
                strcat(record_1.not,record_2.not);
                fwrite(record_1.not,1,2048,pfile);
                fclose(pfile);
                printf("\n  add the note has been success :) ");
                 close();

            }else{
                printf("\n  This option does not exist");
                close();
            }
        }else{
            close();
        }
    }
    close();

}
void view_record(){
    char file[20] ; 
    int pos_ ; 
    strcpy(file,user_interface()); 
    FILE *pfile=NULL ; 
    pfile = fopen(file,"rb+");
    if(pfile== NULL){
        printf("\n    This diary does not existe");
        close();
    }
    else{
        record record_1;
        pos_ = view_existing_record(file); 
        if(pos_ !=0){
            fseek(pfile,pos_,SEEK_SET);
           
            fread(&record_1.name,1,15,pfile);
            fread(&record_1.place,1,20,pfile);
            fread(&record_1.not,1,2048,pfile);
            //strcat(record_1.not,"\0");
            printf("\n Name : %s",record_1.name);
            printf("\n Place : %s ",record_1.place);
            printf("\n My diary  :%s",record_1.not); 
            fclose(pfile);
        }else{
            close();
        }
    }
    close();
}
void menu(){
	system("clear");
	int a;
	printf("\n\n          |||||||| Welcome to \"Diary management\" |||||||| \n");
	printf("\n\n\n     * Creat a new diary management {1} \n");
        printf("\n     * Add    record                {2} \n");
        printf("\n     * View   record                {3} \n");
        printf("\n     * Edit   record                {4} \n");
        printf("\n     * Remove record                {5} \n");
        printf("\n     * Exit                         {6} \n");
	printf("\n\n\n        Enter your choice: ");
	scanf("%d", &a);
	fgetc(stdin); 
	system("clear"); 
	switch (a)
	{
	case 1: diary_management_create();
		break;
	case 2: add_record();
		break;
	case 3: view_record();
		break;
	case 4: edit_record();
		break;
	case 5: remove_record();
		break;
	case 6: exit(-1); 
		break;
	default:
		break;
	}
	
	
	
}
void remove_record(){
    char file[20] ;
    char data[12]; 
    int pos_ ; 
    record record_ ; 
    password pass ; 
    strcpy(file,user_interface()); 
    FILE *pr=NULL,*pw=NULL;
    pr=fopen(file,"rb");
    pw=fopen("temp.bin","wb"); 
    if(pr==NULL){
        printf("Error to open your diary ,try again later :( ");
        close();
    }
    if(pw==NULL){
        printf("Unable to open file temp file.");
        close();
    } 
    fseek(pr,0,SEEK_END);
    int eof=ftell(pr);
    rewind(pr);
    pos_=view_existing_record(file);
    if(pos_!=0){
        fread(&pass,sizeof(pass),1,pr);
        fwrite(&pass,sizeof(pass),1,pw);
        pos_=pos_-12;
        printf("\n%d--%d\n",ftell(pw),ftell(pr));
        while( ftell(pr) != eof){
            if(ftell(pr)==pos_){
                fseek(pr,2095,SEEK_CUR);
            }else{
                fread(&record_,sizeof(record_),1,pr);
                fwrite(&record_,sizeof(record_),1,pw);
            }
        }
    }else{
        printf("\n THIS RECORD DOES NOT EXISTE "); 
        close();
    }
    printf("\n%d--%d",eof,ftell(pw));
    fclose(pr);
    fclose(pw);
    remove(file);
    rename("temp.bin",file); 
    close();
}
void edit_password(char *file){
    system("clear");
    char discrib_[11];
    char dis[11];
    char pass[20],confirm[20];
    FILE* pfile=NULL;
    pfile = fopen(file,"rb+");
    if(!pfile){
        printf("\n  Unable to open %s file ",file);
        close();
    }
    fgetc(stdin);
    fseek(pfile,11,SEEK_SET);
    printf("\n   * Answer the quation !");
    printf("\n\n      *What did they call you when you were younger ? :) ");
    fgets(discrib_,11,stdin);
    fread(dis,1,11,pfile);
    int a = strncmp(dis,discrib_,strlen(dis));
    if(a==0){
        printf("\n\n  Your answer correct ");
            do{
                printf("\n     New Password (8 character) : ");
                fgets(pass, 20, stdin);
                printf("\n     Confirme Password :");
                fgets(confirm, 20, stdin);
            }while( strcmp(pass,confirm) != 0 && strlen(pass)>=8);
            fseek(pfile,12,SEEK_CUR);
            fwrite(pass,1,20,pfile);
            printf("\n\n     Your password changed successfuly :) ");
    }else{   
        printf("\n    Login failed   :( "); 
    }
    fclose(pfile);
    close(); 
}
void birthday(char *file,char *date_today){
    FILE *pfile=NULL;
    char f_date[12];
    pfile=fopen(file,"rb");
    if(!pfile){
        printf("\n Unable to open %s file",file);
        close();
    }
    fseek(pfile,22,SEEK_CUR);
    fread(f_date,1,12,pfile) ; 
    fclose(pfile);
    int i=0,j=0; 
    while(i< strlen(date_today)){
        if((f_date[i]!=date_today[i]) && i>4){
            j++;
        }else{
            j=0;
        }
        i++;
    }
    int k=strlen(file)-4;
    char name[11];
    strncpy(name,file,strlen(file)-4); 
    if(j==0){
        printf("\n\n      Happy birthday Mr %s ",name);
    }
}
int main() {
    menu();
    return 0;
}
