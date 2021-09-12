/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** manage_arg
*/

#include "nm.h"

int noArg(int to_return)
{
    if (fileExist("a.out"))
            nm("a.out");
    else {
        fprintf(stderr, "nm: 'a.out': No such file\n");
        to_return += 1;
    }
    return to_return;
}

int sevralArg(int to_return, char **av)
{
    int i = 1;

    while (av[i] != NULL) {
        if (isDir(av[1])) {
            to_return += 1;
            fprintf(stderr, "nm: Warning: '%s' is a directory\n", av[1]);
        } else if (!fileExist(av[i])) {
            to_return += 1;
            fprintf(stderr, "nm: %s: No such file\n", av[i]);
        } else if (!fileGood(av[i])) {
            to_return += 1;
            fprintf(stderr, "nm: %s: File format not recognized\n", av[i]);
        } else {
            printf("\n");
            printf("%s:\n", av[i]);
            nm(av[i]);
        }
        i++;
    }
    return to_return;
}

int oneArg(int to_return, char **av)
{
    if (isDir(av[1])) {
        to_return += 1;
        fprintf(stderr, "nm: Warning: '%s' is a directory\n", av[1]);
    } else if (!fileExist(av[1])) {
        to_return += 1;
        fprintf(stderr, "nm: '%s': No such file\n", av[1]);
    } else if (!fileGood(av[1])) {
        to_return += 1;
        fprintf(stderr, "nm: %s: File format not recognized\n", av[1]);
    } else {
        nm(av[1]);
    }

    return to_return;
}