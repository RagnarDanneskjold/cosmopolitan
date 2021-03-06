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
.align	16
.text.likely
.source	__FILE__

/	Returns -𝑥, aborting on overflow.
/
/	@param	rdi:rsi is int128 𝑥
/	@return	rdx:rax is -𝑥
/	@see	-ftrapv
__negvti2:
	mov	%rdi,%rax
	mov	%rsi,%rdx
	neg	%rax
	adc	$0,%rdx
/	TODO(jart): Make sure this is correct.
	jo	1f
	neg	%rdx
	jo	1f
	ret
1:	jmp	__on_arithmetic_overflow
	.endfn	__negvti2,globl
