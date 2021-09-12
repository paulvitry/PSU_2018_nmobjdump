/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include  <fcntl.h>
#include  <stdio.h>
#include  <elf.h>
#include  <sys/mman.h>
#include  <sys/stat.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct elf_s
{
    int				fd;
    void			*buf;
    struct stat		s;
    char			*strtab;
    Elf64_Ehdr		*elf;
    Elf64_Shdr		*shdr;
    Elf64_Sym       *symtab;
} elf_t;

typedef struct flags_s
{
    bool    has_reloc;
    bool    exec_p;
    bool    has_lineo;
    bool    has_debug;
    bool    has_syms;
    bool    has_local;
    bool    dynamic;
    bool    wp_text;
    bool    d_paged;
} flags_t;

int noArg(int to_return);

int sevralArg(int to_return, char **av);

int oneArg(int to_return, char **av);

bool    isDir(char *file);

bool    fileGood(char *filename);

bool    fileExist(char *file);

int    objdump(char *filename);

void	printChar(char data);

void    print_ascii(int plus, int *z, unsigned char *w);

flags_t init_flags();

flags_t    get_flags(elf_t elf);

int     get_flags_sum(flags_t flags);

int     get_flags_number(flags_t flags);

void    print_flags(flags_t flags);

#endif /* !OBJDUMP_H_ */
