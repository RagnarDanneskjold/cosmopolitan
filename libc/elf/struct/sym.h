#ifndef COSMOPOLITAN_LIBC_ELF_STRUCT_SYM_H_
#define COSMOPOLITAN_LIBC_ELF_STRUCT_SYM_H_
#include "libc/elf/scalar.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)

typedef struct Elf64_Sym {
  Elf64_Word st_name;
  /* ELF64_ST_TYPE(st_info) → STT_{NOTYPE,OBJECT,FUNC,SECTION,FILE,COMMON,...}
   * ELF64_ST_BIND(st_info) → STB_{LOCAL,GLOBAL,WEAK,...} */
  unsigned char st_info;
  unsigned char st_other;
  Elf64_Section st_shndx;
  Elf64_Addr st_value;
  Elf64_Xword st_size;
} Elf64_Sym;

#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_ELF_STRUCT_SYM_H_ */
