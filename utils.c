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
    int i = 0;
    int numLines = 0;
    char **rows = (char **)malloc(100 * sizeof(char *));
    if ((file = fopen(file_name, "r")) == NULL)
    {
        exit(1);
    }

    while (fgets(line, 50 * sizeof(char), file) != NULL)
    {
        rows[i] = (char *)malloc(50 * sizeof(char));
        strcpy(rows[i], line);
        i++;
        numLines++;
    }
    for (int j = 0; j < numLines; j++)
    {
        strtok(rows[j], "\n");
    }

    fclose(file);
    return rows;
}

int validate_user(char *user, char *pass, char **users)
{
    int num_users = number_of_lines("users.txt");

    for (int j = 0; j < num_users - 1; j++)
    {
        char user_aux[100];
        char *pass_aux;
        strcpy(user_aux, users[j]);
        strtok_r(user_aux, "|", &pass_aux);
        strtok(pass_aux, "\n");

        if (strcmp(user_aux, user) == 0 && strcmp(pass_aux, pass) == 0)
        {
            return 0;
        }
        else if (strcmp(user_aux, user) == 0 && strcmp(pass_aux, pass) != 0)
        {
            return 1;
        }
    }
    return -2;
}
int validate_file(char *file, char *msg, char **files)
{
    int num_files = number_of_lines("files.txt");

    for (int j = 0; j < num_files - 1; j++)
    {
        char file_aux[100];
        char *msg_aux;
        strcpy(file_aux, files[j]);
        strtok_r(file_aux, "|", &msg_aux);
        strtok(msg_aux, "\n");

        if (strcmp(file_aux, file) == 0)
        {
            //substituir o valoe de msg_aux no arquivo para o de msg
            return 1;
        }
        else
        {
            //criar nova entrada no arquivo com msg e file
            return 0;
        }
    }
    return -1;
}

void insert_new_line(char *file_name, char *line, char**file)
{
    FILE *fp;
    int i = 0;
    int num_lines = number_of_lines(file_name);
    char lin[50];
    fp = fopen(file_name, "w+");
    for(i = 0; i < num_lines; i++)
    {
        fprintf(fp,"%s\n", file[i]);
    }
    fprintf(fp,"%s", line);
    fclose(fp);
}

int main()
{
    int num_users = number_of_lines("users.txt");
    char **users;
    users = read_file("users.txt");
    printf("\n\n\n%d", validate_user("teste1", "senha1", users));

    char **files;
    files = read_file("files.txt");
    printf("\n\n\n%d", validate_file("file1", "msg1", files));
    
    char* newline="testenew2|senhanew2";
    insert_new_line("users.txt", newline, users);
    return 0;
}
