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
#include <string.h>
#define MAX_LINE 256

void make_header(){
  FILE *file = fopen("user.csv", "w");
  fprintf(file,"FULL_NAME,AGE,B_TYPE\n");
  fclose(file);
}

int check_first_line() {
  FILE *file = fopen("user.csv", "a+");  // File pointer
  if (file == NULL) { // See if the file is empty 
      return 0;
  }
  char *first_line=(char *)malloc(MAX_LINE*sizeof(char)); // Dynamic memory alocation
  if (fgets(first_line, MAX_LINE, file)) { // See the first line if it exist we do this treatment bellow ↓
      first_line[strcspn(first_line, "\n")] = '\0';  // Remove the newline
      fclose(file); // close the file
      return strcmp(first_line, "FULL_NAME,AGE,B_TYPE") == 0; // See if it equale to the header
  }
  free(first_line); // Free the no used memory
  fclose(file);
  return 0;
}

char* get_info(int index){
  FILE *file=fopen("user.csv","a+");
  int count=-1;
   /* we start the counter from -1 cause we start from the header (line 1) 
   and the first element is on line to so if we want to accesse it like a 
   list we need to do -1 + header = 0 so the first element will be the line two */
  if (file == NULL) {
    perror("Error");
    return '\0';
  }
  char *line=(char *)malloc(MAX_LINE*sizeof(char));
  while (fgets(line,MAX_LINE,file))
  {
    if (count>=index){
      line[strcspn(line, "\n")]='\0';
      fclose(file);
      return line;
    }  
    count++;
  }
  free(line);
  fclose(file);
  return '\0';
}

int get_lines(){
  // calculate how many line in the file
  FILE *file=fopen("user.csv","a+");
  int count=-1;
  if (file == NULL) {
    perror("Error");
    return -1;
  }
  char *line=(char *)malloc(MAX_LINE*sizeof(char));
  while (fgets(line,MAX_LINE,file))
  {  
    count++;
  }
  free(line);
  fclose(file);
  return count;
}

char* get_type(int index){
  // get the blood type
  char *x=(char *)malloc(MAX_LINE*sizeof(char));
  char *type=(char *)malloc(MAX_LINE*sizeof(char));
  x=get_info(index);
  if (x==NULL){
    return '\0';
  }else{
    int c=0;
    x=strtok(x,",");
    x=strtok(NULL,",");
    x=strtok(NULL,",");
  }
  return x;
}

char* get_age(int index){
  // get the blood type
  char *x=(char *)malloc(MAX_LINE*sizeof(char));
  char *type=(char *)malloc(MAX_LINE*sizeof(char));
  x=get_info(index);
  if (x==NULL){
    return '\0';
  }else{
    int c=0;
    x=strtok(x,",");
    x=strtok(NULL,",");
  }
  return x;
}

char* get_name(int index){
  // get the blood type
  char *x=(char *)malloc(MAX_LINE*sizeof(char));
  char *type=(char *)malloc(MAX_LINE*sizeof(char));
  x=get_info(index);
  if (x==NULL){
    return '\0';
  }else{
    int c=0;
    x=strtok(x,",");
  }
  return x;
}

int add_user(char *name,char *age,char *type){
  FILE *file=fopen("user.csv","a+");
  if (file == NULL) { // See if the file is empty 
    return 0;
  }
  fprintf(file,"%s,%s,%s\n",name,age,type);
  fclose(file);
  return 1;
}
