/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** sort
*/

#include "nm.h"

int getLower(int min, int i, elf_t elf)
{
    char *str1 = strToLowerCase(elf.str + elf.symtab[min].st_name);
    char *str2 = strToLowerCase(elf.str + elf.symtab[i].st_name);
    int n1 = 0;
    int n2 = 0;

    while (str1[n1] != '\0' && str2[n2] != '\0') {
        n1 = advance(str1, n1);
        n2 = advance(str2, n2);
        if (str1[n1] < str2[n2])
            return min;
        if (str1[n1] > str2[n2])
            return i;
        ++n1;
        ++n2;
    }
    if (str1[n1] != '\0' && str2[n2] == '\0')
        return i;
    if (str1[n1] == '\0' && str2[n2] != '\0')
        return min;
    if (str1[0] == '_' && str1[1] == '_')
        return i;
    if (strcmp(str2, "__DATA_START") == 0)
        return i;
    if (strcmp(str1, "__DATA_START") == 0)
        return min;
    return min;
}

int *sortMeThis(elf_t elf, int *tab)
{
    int n = 0;
    int i = 0;
    int min = 0;
    int tmp = 0;

    while (tab[n + 1] != -1) {
        min = tab[n];
        i = n + 1;
        while (tab[i] != -1) {
            min = getLower(min, tab[i], elf);
            i++;
        }
        tmp = tab[getIndex(min, tab)];
        tab[getIndex(min, tab)] = tab[n];
        tab[n] = tmp;
        n++;
    }
    return tab;
}

int *sortByName(elf_t elf, int entries)
{
    int *tab = malloc(sizeof(int) * entries + 1);
    int n = 0;

    for (int i = 0; i < entries; i++) {
        if (strcmp(elf.str + elf.symtab[i].st_name, "") != 0
            && badEnding(elf.str + elf.symtab[i].st_name) == true) {
            tab[n] = i;
            n++;
        }
    }
    tab[n] = -1;
    tab = sortMeThis(elf, tab);
    return tab;
}
