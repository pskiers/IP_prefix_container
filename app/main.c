#include "../lib/Ip_v4_prefix.h"
#include "../lib/Prefix_container.h"
#include "Single_container.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


extern Prefix_container CONTAINER;


int main()
{
    int RUN = 1, temp;
    char input[5];
    unsigned int base;
    char mask;
    int err;
    printf("Welcome to this simple programme that manages your IP prefixes!\nType 'help' for additional information\n\n");
    while (RUN)
    {
        printf("\nEnter command: ");
        scanf("%s", input);
        while ((getchar()) != '\n'); // clear input buffer
        if (strcmp(input, "exit") == 0)
        {
            RUN = 0;
            printf("\nLeaving...\n");
        }
        else if (strcmp(input, "help") == 0)
        {
            printf("\nAvailable commands:\n");
            printf("\t'help' - displays additional informations\n");
            printf("\t'exit' - ends the programme\n");
            printf("\t'add' - add prefix to the container\n");
            printf("\t'del' - deletes prefix from the container\n");
            printf("\t'check' - checks if address is in the container\n");
        }
        else if (strcmp(input, "add") == 0)
        {
            printf("\nEnter base of the prefix (hex): ");
            scanf("%x", &base);
            while ((getchar()) != '\n'); // clear input buffer
            printf("\nEnter mask of the prefix: ");
            scanf("%d", &temp);
            mask = (char) temp;
            while ((getchar()) != '\n'); // clear input buffer
            err = add(base, mask);
            if (err)
                printf("\nPrefix already in the container or entered incorrect prefix\n");
            else
                printf("\nPrefix added to the container\n");
        }
        else if (strcmp(input, "del") == 0)
        {
            printf("\nEnter base of the prefix (hex): ");
            scanf("%x", &base);
            while ((getchar()) != '\n'); // clear input buffer
            printf("\nEnter mask of the prefix: ");
            scanf("%d", &temp);
            mask = (char) temp;
            while ((getchar()) != '\n'); // clear input buffer
            err = del(base, mask);
            if (err)
                printf("\nPrefix not in the container or entered incorrect prefix\n");
            else
                printf("\nPrefix deleted from the container\n");
        }
        else if (strcmp(input, "check") == 0)
        {
            printf("\nEnter IP address to check (hex): ");
            scanf("%x", &base);
            while ((getchar()) != '\n'); // clear input buffer
            mask = check(base);
            if (mask == -1)
                printf("\nAddress not in the container\n");
            else
                printf("The smallest prefix containing address: mask lenght = %d", mask);
        }
        else
            printf("\nIncorrect command\n");
    }
    destroy();
    printf("Programm ended\n");
    return 0;
}