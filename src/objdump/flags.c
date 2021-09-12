/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** flags
*/

#include "objdump.h"


flags_t init_flags()
{
    flags_t flags;

    flags.has_reloc = false;
    flags.exec_p = false;
    flags.has_lineo = false;
    flags.has_debug = false;
    flags.has_syms = false;
    flags.has_local = false;
    flags.dynamic = false;
    flags.wp_text = false;
    flags.d_paged = false;

    return flags;
}

flags_t    get_flags(elf_t elf)
{
    flags_t flags = init_flags();

    if (elf.elf->e_phnum != 0)
        flags.d_paged = true;
    if (elf.elf->e_type == ET_EXEC)
        flags.exec_p = true;
    if (elf.elf->e_type == ET_DYN)
        flags.dynamic = true;
    for (int i = 0; i < elf.elf->e_shnum; i++) {
        if (elf.shdr[i].sh_type == SHT_SYMTAB
                || elf.shdr[i].sh_type == SHT_DYNAMIC)
            flags.has_syms = true;
        if (elf.shdr[i].sh_type == SHT_REL && elf.elf->e_type == ET_REL)
            flags.has_reloc = true;
        if (elf.shdr[i].sh_type == SHT_RELA && elf.elf->e_type == ET_REL)
            flags.has_reloc = true;
    }
    return flags;
}

int     get_flags_sum(flags_t flags)
{
    int result = 0;

    if (flags.has_reloc == true)
        result += 1;
    if (flags.exec_p == true)
        result += 2;
    if (flags.has_syms == true)
        result += 10;
    if (flags.dynamic == true)
        result += 40;
    if (flags.d_paged == true)
        result += 100;
    return result;
}

int     get_flags_number(flags_t flags)
{
    int result = 0;

    if (flags.has_reloc == true)
        result += 1;
    if (flags.exec_p == true)
        result += 1;
    if (flags.has_syms == true)
        result += 1;
    if (flags.dynamic == true)
        result += 1;
    if (flags.d_paged == true)
        result += 1;
    return result;
}

void    print_flags(flags_t flags)
{
    int c = get_flags_number(flags);

    if (flags.has_reloc == true && c != 1) {
        printf("HAS_RELOC, ");
        c--;
    } else if (flags.has_reloc == true && c == 1)
        printf("HAS_RELOC\n");
    if (flags.exec_p == true && c != 1) {
        printf("EXEC_P, ");
        c--;
    } else if (flags.exec_p == true && c == 1)
        printf("EXEC_P\n");
    if (flags.has_syms == true && c != 1) {
        printf("HAS_SYMS, ");
        c--;
    } else if (flags.has_syms == true && c == 1)
        printf("HAS_SYMQ\n");
    if (flags.dynamic == true && c != 1) {
        printf("DYNAMIC, ");
        c--;
    } else if (flags.dynamic == true && c == 1)
        printf("DYNAMIC\n");
    if (flags.d_paged == true && c != 1) {
        printf("D_PAGED, ");
        c--;
    } else if (flags.d_paged == true && c == 1)
        printf("D_PAGED\n");
}