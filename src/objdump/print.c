/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** print
*/

#include "objdump.h"

void	printChar(char data)
{
    if (data < 32)
        printf(".");
    else if (data > 126)
        printf(".");
    else
        printf("%c", data);
}

void    print_ascii(int plus, int *z, unsigned char *w)
{
    int x;

    x = plus;
    while (x % 16 != 0) {
        if (x % 4 == 0 && x % 16)
            printf(" ");
        printf("  ");
        ++x;
    }
    printf("  ");
    while (*z < plus) {
        printChar(w[*z]);
        (*z)++;
    }
    while ((*z)++ % 16 != 0)
        printf(" ");
    *z = plus;
    printf("\n");
}
