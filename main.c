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
#include <stdlib.h>
#include <ctype.h>
#include "file_manipulation.c"

int add_user_fun();
int find_comp();
int list_user();
int valid_name(char *s);
int valid_age();
int valid_type();

char *types[8]={"ab+","ab-","a+","a-","b+","b-","o+","o-"};

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




int main(){
  while (1)
  {
    int size=MAX_LINE;
    char *x=(char*)malloc(size*sizeof(char));
    char *ptr;
    if (x == NULL) {
      perror("Memory allocation failed");
      return 1;
    }

    printf("+-----+-----------------------+"
  "\n|  1  | exit                  |"
  "\n+-----+-----------------------+"
  "\n|  2  | add user              |"
  "\n+-----+-----------------------+"
  "\n|  3  | find compatible user  |"
  "\n+-----+-----------------------+"
  "\n|  4  | list user             |"
  "\n+-----+-----------------------+"
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
      if (strtol(x,&ptr,10)==1 && *ptr=='\0' || strcmp(x,"exit")==0) {free(x);printf("Exiting"); return 0;}
      else if (strtol(x,&ptr,10)==2  && *ptr=='\0'){
        free(x);
        if(!check_first_line()) make_header();
        add_user_fun();
        break;
      }
      else if (strtol(x,&ptr,10)==3  && *ptr=='\0'){continue;}
      else if (strtol(x,&ptr,10)==4  && *ptr=='\0'){continue;}
    }
  }
  return 0;
}

int valid_name(char *s){
  while (*s)
  {
    if(!isalpha(tolower(*s)) && *s!=' '){
      return 1;
    }
    s++;
  }
  return 0;
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

int add_user_fun(){
  char name[50],age[50],type[50];
  char *b=(char*)malloc(50*sizeof(char)); // user input
  if (b == NULL) {
    perror("Memory allocation failed");
    return -1;
  }
  do
  {
    printf("enter a name> ");
    scanf("%s",b);
  } while (valid_name(b) || strlen(b)>=50); // see if the user type more than 50 char or if the name is valid
  strcpy(name,b); // copy the input text to the variable 

  do
  {
    printf("enter a age> ");
    scanf("%s",b);
  } while (valid_age(b) || strlen(b)>=50);strcpy(age,b);

  do
  {
    printf("enter a blood type> ");
    scanf("%s",b);
  } while (valid_type(b) || strlen(b)>=50);strcpy(type,b);

  free(b);
  int user=add_user(name,age,type);
  if (user==1){
    printf("user added\n\n");
  }else{
    perror("Error\n");
  }
  return user;
}

