/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** utils
*/

#include "nm.h"

bool    isContained(int *arr, int i)
{
    for (int n = 0; arr[n] != -1; n++) {
        if (arr[n] == i)
            return true;
    }
    return false;
}

int array_len(int *tab)
{
    int i = 0;

    while (tab[i] != -1)
        i++;
    return i;
}

char    *strToLowerCase(char *str)
{
    char *new = malloc(strlen(str));
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z')
            new[i] = str[i] - 32;
        else
            new[i] = str[i];
        i++;
    }
    return new;
}

bool    badEnding(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    i--;
    if (str[i] == 'c' && str[i - 1] == '.')
        return false;
    return true;
}

int getIndex(int n, int *tab)
{
    for (int i = 0; tab[i] != -1; i++) {
        if (tab[i] == n)
            return i;
    }
    return -1;
}
