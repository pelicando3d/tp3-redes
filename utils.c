#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/queue.h>


int number_of_lines(char *file_name)
{
    FILE *file;
    char line[50];
    int numLines = 0;

    if ((file = fopen(file_name, "r")) == NULL)
    {
        exit(1);
    }

    while (fgets(line, sizeof line, file) != NULL)
    {
        numLines++;
    }

    fclose(file);
    return numLines;
}

char **read_file(char *file_name)
{
    FILE *file;
    char line[50];
    int i, j, numLines = 0;
    char **rows = (char **)malloc(100 * sizeof(char *));
    if ((file = fopen(file_name, "r")) == NULL)
    {
        exit(1);
    }

    while (fgets(line, sizeof line, file) != NULL)
    {
        rows[i] = (char *)malloc(50 * sizeof(char));
        rows[i] = strdup(line);
        i++;
        numLines++;
    }
    for (j = 0; j < numLines; j++)
    {
        strtok(rows[j], "\n");
    }

    fclose(file);
    return rows;
}

int validate_user(char* user, char* pass, char **users)
{
    int num_users = number_of_lines("users.txt");
    int j;
    for (j = 0; j < num_users-1; j++)
    {

        /*  strtok(users[j], "\n"); */

        char *user_aux, *pass_aux;
        strcpy(user_aux, users[j]);
        strtok_r(user_aux, "|", &pass_aux);
        strtok(pass_aux, "\n");


        if(strcmp(user_aux, user) == 0 && strcmp(pass_aux,pass) == 0)
            return 0;
        else if(strcmp(user_aux, user) == 0 && strcmp(pass_aux,pass) != 0)
            return -1;
    }
    return -2;
}

/* int main()
{
    char **users = (char**)malloc(100*sizeof(char*));
    int i = 0;
    int num_users = number_of_lines("users.txt");
    for(i = 0; i < num_users; i++){
        users[i] = (char*)malloc(50*sizeof(char));
    }
    users = read_file("users.txt");
    fflush(stdout);
    printf("\n\n\n%d", validate_user("teste1", "senha1", users));

    // char **files = (char**)malloc(100*sizeof(char*));
    // i = 0;
    // int num_files = number_of_lines("files.txt");
    // for(i = 0; i < num_files; i++){
    //     files[i] = (char*)malloc(50*sizeof(char));
    // }
    // files = read_file("files.txt");

    return 0;
} */
