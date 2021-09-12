/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** utils2
*/

#include "nm.h"


bool    checkBegin(char *str)
{
    if (str[0] == 'w' && str[1] == 'm' && str[2] == '4' && str[3] == '.')
        return false;
    return true;
}

void    print_nm(elf_t elf, int entries)
{
    int *tab;

    tab = sortByName(elf, entries);
    for (int i = 0; i < array_len(tab); i++) {
        if (print_type(elf.symtab[tab[i]], elf.sections) == 'U'
            || print_type(elf.symtab[tab[i]], elf.sections) == 'w') {
            printf("                 %c %s\n",
                print_type(elf.symtab[tab[i]], elf.sections),
                elf.str + elf.symtab[tab[i]].st_name);
        } else {
            printf("%016x %c %s\n", (unsigned) elf.symtab[tab[i]].st_value,
                    print_type(elf.symtab[tab[i]],
                    elf.sections), elf.str + elf.symtab[tab[i]].st_name);
        }
    }
}

int advance(char *str, int i)
{
    while ((str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9'))
        i++;
    return i;
}
