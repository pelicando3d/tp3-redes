#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/queue.h>

char **read_file(char *file_name)
{
    FILE *file;
    char line[50];
    int i, numLines = 0;
    char ** rows = malloc(100*sizeof(char*));
    if ((file = fopen(file_name, "r")) == NULL)
    {
        exit(1);
    }

   while(fgets(line, sizeof line, file)!=NULL) {
        //check to be sure reading correctly

        //add each filename into array of programs
        rows[i]= malloc(50*sizeof(char));
        rows[i]=strdup(line); 
        i++;
        //count number of programs in file
        numLines++;
    }
    //check to be sure going into array correctly 
    for (int j=0 ; j<numLines; j++) {
        strtok(rows[j], "\n");
        // printf("\n%s", rows[j]);
    }

    fclose(file);
    return rows;
}
int number_of_lines(char* file_name)
{
    FILE *file;
    char line[50];
    int numLines = 0;

    if ((file = fopen(file_name, "r")) == NULL)
    {
        exit(1);
    }

   while(fgets(line, sizeof line, file)!=NULL) {
        numLines++;
    }

    fclose(file);
    return numLines;
}

int validate_user(char user[15], char pass[15], char **users)
{
    // char str[40] = "";
    // strcat(str,user);
    // strcat(str,"|");
    // strcat(str,pass);
    // printf("\n%s", str);
    int num_users = number_of_lines("users.txt");
    for (int j=0 ; j<num_users; j++) 
    {
        strtok(users[j], "\n");
        printf("\n%s", users[j]);
        char*user_aux, *pass_aux;
        strcpy(user_aux, users[j]);
        strtok_r(user_aux, "|", &pass_aux);
        printf("'%s' '%s'", user_aux, pass_aux);
    }
}

int main()
{
    char **files = read_file("files.txt");
    char **users = read_file("users.txt");
    printf("%s", files[0]);
    validate_user("teste1", "senha1", files);
    return 0;
}
