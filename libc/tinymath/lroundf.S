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

/	Rounds to nearest integer, away from zero.
/
/	@param	𝑥 is float scalar in low quarter of %xmm0
/	@return	64-bit signed integer in %rax
/	@see	round()
tinymath_lroundf:
	.leafprologue
	.profilable
	movss	A(%rip),%xmm1
	movss	B(%rip),%xmm2
	andps	%xmm0,%xmm2
	orps	%xmm2,%xmm1
	addss	%xmm0,%xmm1
	cvttss2siq %xmm1,%rax
	.leafepilogue
	.endfn	tinymath_lroundf,globl
	.alias	tinymath_lroundf,lroundf
	.alias	tinymath_lroundf,llroundf

	.rodata.cst4
A:	.long	0x3effffff
	.rodata.cst16
B:	.long	0x80000000,0,0,0
