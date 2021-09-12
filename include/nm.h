/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


typedef struct elf_s
{
    Elf64_Ehdr      *elf;
    Elf64_Shdr      *sections, *strtab;
    Elf64_Sym       *symtab;
    char *str;
} elf_t;

int noArg(int to_return);

int sevralArg(int to_return, char **av);

int oneArg(int to_return, char **av);

bool    fileGood(char *filename);

bool    fileExist(char *file);

bool    isContained(int *arr, int i);

int array_len(int *tab);

char    *strToLowerCase(char *str);

bool    badEnding(char *str);

int getIndex(int n, int *tab);

int getLower(int min, int i, elf_t elf);

int *sortMeThis(elf_t elf, int *tab);

int *sortByName(elf_t elf, int entries);

bool    checkBegin(char *str);

void    print_nm(elf_t elf, int entries);

int advance(char *str, int i);

void    *getBuffer(const char *filename);

char    print_type(Elf64_Sym sym, Elf64_Shdr *shdr);

void    nm(const char *filename);

bool    isDir(char *file);

#endif /* !NM_H_ */
