/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 tw=8 fenc=utf-8                                     :vi│
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

log1pf:	push	%rbp
	mov	%rsp,%rbp
	.profilable
	push	%rax
	vmovss	%xmm0,-4(%rbp)
	flds	-4(%rbp)
	fld	%st
	fabs
	fldt	.LC16(%rip)
	fxch	%st(1)
	fcomip	%st(1),%st
	fstp	%st
	jnb	2f
	fldln2
	fxch	%st(1)
	fyl2xp1
1:	fstps	-4(%rbp)
	vmovss	-4(%rbp),%xmm0
	leave
	ret
2:	fld1
	faddp	%st,%st(1)
	fldln2
	fxch	%st(1)
	fyl2x
	jmp	1b
	.endfn	log1pf,globl

	.section .rodata.cst16,"aM",@progbits,16
	.align	16
.LC16:	.long	205731576
	.long	2515933592
	.long	16381
	.long	0
	.previous
