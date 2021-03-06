/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/elf/def.h"
#include "libc/elf/elf.h"

Elf64_Shdr *getelfsectionbyaddress(const Elf64_Ehdr *elf, size_t mapsize,
                                   void *addr) {
  Elf64_Half i;
  Elf64_Shdr *shdr;
  if (elf) {
    for (i = elf->e_shnum; i > 0; --i) {
      shdr = getelfsectionheaderaddress(elf, mapsize, i - 1);
      if ((intptr_t)addr >= shdr->sh_addr &&
          (intptr_t)addr < shdr->sh_addr + shdr->sh_size) {
        return shdr;
      }
    }
  }
  return NULL;
}
