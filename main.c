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




int main(){
  int size=MAX_LINE;
  char *x=(char*)malloc(size*sizeof(char));
  char *ptr;
  if (x == NULL) {
    perror("Memory allocation failed");
    return 1;
  }

  printf("+-----+-----------------------+"
"\n|  0  | exit                  |"
"\n+-----+-----------------------+"
"\n|  1  | add user              |"
"\n+-----+-----------------------+"
"\n|  2  | find compatible user  |"
"\n+-----+-----------------------+"
"\n|  3  | list user             |"
"\n+-----+-----------------------+"
"\n\n>");

  while (1)
  {
    int index=0;
    char c;
    while ((c=getchar())!='\n' && c!='\0')
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
    if (strtol(x,&ptr,10)==0 && *ptr=='\0' || strcmp(x,"exit")==0) {printf("Exiting"); return 0;}
    else if (strtol(x,&ptr,10)==1  && *ptr=='\0'){continue;}
    else if (strtol(x,&ptr,10)==2  && *ptr=='\0'){continue;}
    printf(">");
  }
    
  
  return 0;
}