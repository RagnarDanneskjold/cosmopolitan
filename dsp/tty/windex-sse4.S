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

/	Returns index of minimum positive int16 in array.
/
/	@param	rdi points to nonempty array
/	@param	esi is 16-byte aligned 8+ / 8 multiple array item count
/	@note	needs sse4 (nehalem+)
windex$sse4:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	$8,%eax
	sub	$32,%rsp
	movdqa	(%rdi),%xmm2
	movdqa	.Lidx(%rip),%xmm1
	movdqa	.Linc(%rip),%xmm6
	movdqa	%xmm1,%xmm3
0:	cmp	%eax,%esi
	je	1f
	add	$8,%eax
	movdqa	-16(%rdi,%rax,2),%xmm4
	movdqa	%xmm2,%xmm7
	movdqa	%xmm3,%xmm5
	paddw	%xmm6,%xmm5
	movdqa	%xmm5,%xmm3
	pcmpgtw	%xmm4,%xmm7
	pminsw	%xmm4,%xmm2
	movdqa	%xmm7,%xmm0
	pblendvb %xmm0,%xmm5,%xmm1
	jmp	0b
1:	phminposuw %xmm2,%xmm0
	movd	%xmm0,%eax
	movdqa	%xmm1,-32(%rbp)
	shr	$16,%eax
	movzwl	-32(%rbp,%rax,2),%eax
	leave
	ret
	.endfn	windex$sse4,globl

	.rodata.cst16
.Lidx:	.short	0,1,2,3,4,5,6,7
.Linc:	.value	8,8,8,8,8,8,8,8
