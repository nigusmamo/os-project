#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int choice;
    char name[100];
    char currentDir[256];
    char temp;
    FILE *fp;
    char text[500];

    chdir(getenv("HOME"));

    while (1)
    {
        getcwd(currentDir, sizeof(currentDir));

        printf("\n==== Simple Ubuntu Terminal Emulator ====\n");
        printf("Current Directory: %s\n", currentDir);
        printf("-------------------------------------------\n");
        printf("1. Show current directory (pwd)\n");
        printf("2. Change directory (cd)\n");
        printf("3. List files (ls)\n");
        printf("4. Make directory (mkdir)\n");
        printf("5. Remove directory (rmdir)\n");
        printf("6. Create file (touch)\n");
        printf("7. Show file content (cat)\n");
        printf("8. Write text to file (write)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while ((temp = getchar()) != '\n' && temp != EOF)
            ;

        switch (choice)
        {
        case 1:
            printf("Current Directory: %s\n", currentDir);
            break;

        case 2:
            printf("Enter directory name ('..' to go back, '~' for home): ");
            scanf("%99s", name);
            if (strcmp(name, "~") == 0)
            {
                chdir(getenv("HOME"));
                printf("Returned to home directory.\n");
            }
            else if (strcmp(name, "..") == 0)
            {
                chdir("..");
                printf("Returned to previous directory.\n");
            }
            else if (chdir(name) == 0)
            {
                printf("Directory changed to: %s\n", name);
            }
            else
            {
                perror("cd failed");
            }
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            break;

        case 3:
            system("ls --color=auto");
            break;

        case 4:
            printf("Enter new directory name: ");
            scanf("%99s", name);
            char mkdirCmd[120];
            sprintf(mkdirCmd, "mkdir %s", name);
            if (system(mkdirCmd) == 0)
                printf("Directory '%s' created successfully.\n", name);
            else
                printf("Failed to create directory.\n");
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            break;

        case 5:
            printf("Enter directory name to remove: ");
            scanf("%99s", name);
            char rmdirCmd[120];
            sprintf(rmdirCmd, "rmdir %s", name);
            if (system(rmdirCmd) == 0)
                printf("Directory '%s' removed successfully.\n", name);
            else
                printf("Failed to remove directory (maybe not empty).\n");
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            break;

        case 6:
            printf("Enter file name to create: ");
            scanf("%99s", name);
            char touchCmd[120];
            sprintf(touchCmd, "touch %s", name);
            if (system(touchCmd) == 0)
                printf("File '%s' created successfully.\n", name);
            else
                printf("Failed to create file.\n");
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            break;

        case 7:
            printf("Enter file name to read: ");
            scanf("%99s", name);
            fp = fopen(name, "r");
            if (fp == NULL)
            {
                printf("Error: Could not open file '%s'.\n", name);
            }
            else
            {
                printf("\n--- File Content (%s) ---\n", name);
                char ch;
                while ((ch = fgetc(fp)) != EOF)
                {
                    putchar(ch);
                }
                fclose(fp);
                printf("\n--- End of File ---\n");
            }
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            break;

        case 8:
            printf("Enter file name to write into: ");
            scanf("%99s", name);
            while ((temp = getchar()) != '\n' && temp != EOF)
                ;
            fp = fopen(name, "a");
            if (fp == NULL)
            {
                printf("Error: Could not open file '%s' for writing.\n", name);
            }
            else
            {
                printf("Enter text to write (end with a single line containing 'END'):\n");
                while (1)
                {
                    fgets(text, sizeof(text), stdin);
                    if (strncmp(text, "END", 3) == 0)
                        break;
                    fputs(text, fp);
                }
                fclose(fp);
                printf("Text written successfully to '%s'.\n", name);
            }
            break;

        case 9:
            printf("Exiting terminal emulator...\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
