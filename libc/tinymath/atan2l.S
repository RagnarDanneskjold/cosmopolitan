/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 sw=8 fenc=utf-8                                     :vi│
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
#include "libc/macros.h"
.source	__FILE__

/	Returns arc tangent of 𝑦/𝑥.
/
/	@param	𝑥 is an 80-bit long double passed on stack in 16-bytes
/	@param	𝑦 is an 80-bit long double passed on stack in 16-bytes
/	@return	result of computation on FPU stack in %st
tinymath_atan2l:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	fldt	16(%rbp)
	fldt	32(%rbp)
	fpatan
	pop	%rbp
	ret
	.endfn	tinymath_atan2l,globl
	.alias	tinymath_atan2l,atan2l
