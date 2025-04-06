/*
           ▄▄▄       ▄████▄   ██░ ██ 
          ▒████▄    ▒██▀ ▀█  ▓██░ ██▒
          ▒██  ▀█▄  ▒▓█    ▄ ▒██▀▀██░
          ░██▄▄▄▄██ ▒▓▓▄ ▄██▒░▓█ ░██ 
           ▓█   ▓██▒▒ ▓███▀ ░░▓█▒░██▓
           ▒▒   ▓▒█░░ ░▒ ▒  ░ ▒ ░░▒░▒
            ▒   ▒▒ ░  ░  ▒    ▒ ░▒░ ░
            ░   ▒   ░         ░  ░░ ░
            ░  ░░ ░       ░  ░  ░
            ░                
*/
/*
  En: This project is carried out for academic purposes
  Fr: Ce projet est réalisé à des fins académiques
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include "file_manipulation.c"

int add_user_fun();
int find_donnor();
int find_reciver();
int list_user();
int valid_name();
int valid_age();
int valid_type();

char *types[8]={"ab+","ab-","a+","a-","b+","b-","o+","o-"};
char *donnor[8][8]={
  {"ab+", "ab-", "a+", "a-", "b+", "b-", "o+", "o-"},
  {"ab-", "a-", "b-", "o-", NULL, NULL, NULL, NULL},
  {"a+", "a-", "o+", "o-", NULL, NULL, NULL, NULL},
  {"a-", "o-", NULL, NULL, NULL, NULL, NULL, NULL},
  {"b+", "b-", "o+", "o-", NULL, NULL, NULL, NULL},
  {"b-", "o-", NULL, NULL, NULL, NULL, NULL, NULL},
  {"o+", "o-", NULL, NULL, NULL, NULL, NULL, NULL},
  {"o-", NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};
char *reciver[8][8]={
  {"ab+",  NULL, NULL, NULL, NULL, NULL, NULL, NULL},
  {"ab+", "ab-", NULL, NULL, NULL, NULL, NULL, NULL},
  {"ab+", "a+", NULL, NULL, NULL, NULL, NULL, NULL},
  {"ab+", "ab-", "a+", "a-", NULL, NULL, NULL, NULL},
  {"ab+", "b+", NULL, NULL, NULL, NULL, NULL, NULL},
  {"ab+", "ab-", "b+", "b-", NULL, NULL, NULL, NULL},
  {"ab+", "a+", "b+", "o+", NULL, NULL, NULL, NULL},
  {"ab+", "ab-", "a+", "a-", "b+", "b-", "o+", "o-"},
};

/*
+-----+-----------------------+
|  0  | exit                  |
+-----+-----------------------+
|  1  | add user              |
+-----+-----------------------+
|  2  | find compatible user  |
+-----+-----------------------+
|  3  | list user             |
+-----+-----------------------+
*/

/*
23
+---------+-----------------------------------------+---------+---------+
|    0    | exit                                    |   18    |   ab+   |
+---------+-----------------------------------------+---------+---------+
|    1    | add user                                |   100   |   ab-   |
+---------+-----------------------------------------+---------+---------+
|    2    | Full Name                               |   20    |   o-    |
+---------+-----------------------------------------+---------+---------+
|    3    | list user                               |   35    |   a+    |
+---------+-----------------------------------------+---------+---------+
*/

/*
  for (int i = 0; i < 8; i++)
  {
    printf("%s ",*(acquire[4]+i));
  }
*/

int main(){
  while (1)
  {
    int size=MAX_LINE;
    char *x=(char*)malloc(size*sizeof(char)),*ptr;
    if (x == NULL) {
      perror("Memory allocation failed");
      return 1;
    }

    printf(
    "+-----+------------------------+"
  "\n|  1  | sortir du programme    |"
  "\n+-----+------------------------+"
  "\n|  2  | ajouter un utilisateur |"
  "\n+-----+------------------------+"
  "\n|  3  | trouver un donateur    |"
  "\n+-----+------------------------+"
  "\n|  4  | trouver un receveur    |"
  "\n+-----+------------------------+"
  "\n|  5  | liste des utilisateurs |"
  "\n+-----+------------------------+"
  "\n\n>");


    while (1){
      int index=0;
      char c;
      while ((c=getchar())!='\n')
      {
        if (c==' ' && index==0)
        {
          continue;
        }
        if(index>=size-1){
          size+=MAX_LINE;
          x=realloc(x,size*sizeof(char));
        }
        x[index++]=tolower(c);
      }
      x[index++]='\0';
      if (strtol(x,&ptr,10)==1 && *ptr=='\0' || strcmp(x,"exit")==0) {free(x);printf("Sortie");Sleep(1000); return 0;}
      else if (strtol(x,&ptr,10)==2  && *ptr=='\0'){
        free(x);
        if(!check_first_line()) make_header();
        add_user_fun();
        break;
      }
      else if (strtol(x,&ptr,10)==3  && *ptr=='\0'){
        free(x);
        find_donnor();
        break;
      }
      else if (strtol(x,&ptr,10)==4  && *ptr=='\0'){
        free(x);
        find_reciver();
        break;
      }
      else if (strtol(x,&ptr,10)==5  && *ptr=='\0'){
        free(x);
        if(!check_first_line() || get_lines()==0) {printf("\naucun utilisateur trouver\n\n");make_header();break;};
        list_user();
        break;
      }
    }
  }
  return 0;
}
// fontion de condition pour l'ajout des utilisateur

int valid_name(char *s){
  int has_letter = 1;

  for (int i = 0; s[i] != '\0'; i++) {
      if (isalpha(s[i])) {
          has_letter = 0;
      } else if (!isspace(s[i])) {
          return 1;
      }
  }
  return has_letter;
}

int valid_age(char *s){
  while (*s)
  {
    if(!isdigit(*s)){
      return 1;
    }
    s++;
  }
  return 0;
}

// vtransformer une chaine de char en chaine de char en miniscule 

char* strlower(char *s){
  for (int i = 0; i < strlen(s); i++)
  {
    *(s+i)=tolower(*(s+i));
  }
  return s;
}

int valid_type(char *s){
  for (int i = 0; i < 8; i++)
  {
    if (strcmp(*(types+i),s)==0)
    {
      return 0;
    } 
  }
  return 1;
}


// main funcs

// ajouter les utilisateur
int add_user_fun(){
  char name[40],age[40],type[40];
  char *b=(char*)malloc(40*sizeof(char)),*endptr; // user input
  if (b == NULL) {
    perror("Memory allocation failed");
    return -1;
  }
  do
  {
    printf("enter le nom du patient> ");
    fgets(b, 40, stdin);
    b[strcspn(b, "\n")] = '\0';
  } while (valid_name(b) || strlen(b)>=40); // see if the user type more than 50 char or if the name is valid
  strcpy(name,b); // copy the input text to the variable 

  do
  {
    printf("enter l'age du patient> ");
    fgets(b, 40, stdin);
    b[strcspn(b, "\n")] = '\0';
  } while (valid_age(b) || strlen(b)>=40 || strtol(b,&endptr,10)==0);strcpy(age,b);
  printf(
    "\n%33s\n"
    "+-----+-----+-----+-----+-----+-----+-----+-----+\n"
    "|  o- |  o+ | ab- | ab+ |  a- |  a+ | b-  | b+  |\n"
    "+-----+-----+-----+-----+-----+-----+-----+-----+\n\n","LES TYPES DE SANG");
  do
  {
    printf("enter le type de sang du patient> ");
    fgets(b, 40, stdin);
    b[strcspn(b, "\n")] = '\0';
    strlower(b);
  } while (valid_type(b) || strlen(b)>=40);strcpy(type,b);

  free(b);
  int user=add_user(name,age,type);
  if (user==1){
    printf("utilisateur ajouter\n\n");
  }else{
    perror("Error\n");
  }
  return user;
}
// lister les utilisateur
int list_user(){
  printf("\n\n%46s\n","LISTE D'UTILISATEUR");
  for (int i = 0; i < get_lines(); i++)
  {
    printf(
      "+---------+-----------------------------------------+---------+---------+\n"
      "|    %-5d| %-40s|   %-6s|   %-6s|\n",i,get_name(i),get_age(i),get_type(i));
  }
  printf("+---------+-----------------------------------------+---------+---------+\n\n");
  Sleep(500);
}
// trouver les doneur
int find_donnor(){
  if(!check_first_line() || get_lines()==0) {
    printf("\nno user found\n\n");
    make_header();
    return -1;
  }
  list_user();
  char *b=(char *)malloc(MAX_LINE*sizeof(char)),*endptr,*type;
  int pos,index,count=0;
  do{
    printf("enter l'id de l'utilisateur> ");
    fgets(b, 40, stdin);
    b[strcspn(b,"\n")]='\0';
    pos=(int)strtol(b,&endptr,10);
  }while(strlen(b)>100 || strlen(b)<=0 || pos<0 || pos>=get_lines() || *endptr!='\0');
  free(b);
  for (int i=0 ;i < 8; i++){
    if(strcmp(types[i],get_type(pos))==0){
      index=i;
      break;
    }
  }
  printf("\n\n%43s\n","LISTE DES DONNEUR");
  for (int i = 0; i < get_lines(); i++){
    if(pos==i){
      continue;
    }
    for (int j=0; j<8; j++){
      if (*(donnor[index]+j)==NULL) continue;
      if(strcmp(*(donnor[index]+j),get_type(i))==0){
        count++;
        printf(
          "+---------+-----------------------------------------+---------+---------+\n"
          "|    %-5d| %-40s|   %-6s|   %-6s|\n",i,get_name(i),get_age(i),get_type(i)
        );
        break;
      }
    }
  }
  if (count!=0){
    printf("+---------+-----------------------------------------+---------+---------+\n\n");
  }else{
    printf(
      "+-----------------------------------------------------------------------+\n"
      "+                       AUCUN UTILISATEUR TROUVER                       +\n"
      "+-----------------------------------------------------------------------+\n\n"
    );
  }
  Sleep(1000);
  return 0;
}
// trouver les receveur
int find_reciver(){
  if(!check_first_line() || get_lines()==0) {
    printf("\nno user found\n\n");
    make_header();
    return -1;
  }
  list_user();
  char *b=(char *)malloc(MAX_LINE*sizeof(char)),*endptr,*type;
  int pos,index,count=0;
  do{
    printf("enter l'id de l'utilisateur> ");
    fgets(b, 40, stdin);
    b[strcspn(b,"\n")]='\0';
    pos=(int)strtol(b,&endptr,10);
  }while(strlen(b)>100 || strlen(b)<=0 || pos<0 || pos>=get_lines() || *endptr!='\0');
  free(b);
  for (int i=0 ;i < 8; i++){
    if(strcmp(types[i],get_type(pos))==0){
      index=i;
      break;
    }
  }
  printf("\n\n%45s\n","LISTE DES RECEVEUR");
  for (int i = 0; i < get_lines(); i++){
    if(pos==i){
      continue;
    }
    for (int j=0; j<8; j++){
      if (*(reciver[index]+j)==NULL) continue;
      if(strcmp(*(reciver[index]+j),get_type(i))==0){
        count++;
        printf(
          "+---------+-----------------------------------------+---------+---------+\n"
          "|    %-5d| %-40s|   %-6s|   %-6s|\n",i,get_name(i),get_age(i),get_type(i)
        );
        break;
      }
    }
  }
  if (count!=0){
    printf("+---------+-----------------------------------------+---------+---------+\n\n");
  }else{
    printf(
      "+-----------------------------------------------------------------------+\n"
      "+                       AUCUN UTILISATEUR TROUVER                       +\n"
      "+-----------------------------------------------------------------------+\n\n"
    );
  }
  Sleep(1000);
  return 0;
}