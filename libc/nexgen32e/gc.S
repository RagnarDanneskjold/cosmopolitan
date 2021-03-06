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
#include "libc/dce.h"
#include "libc/notice.inc"
#define INITIAL_CAPACITY 4

/	Invokes deferred function calls.
/
/	This offers behavior similar to std::unique_ptr. Functions
/	overwrite their return addresses jumping here, and pushing
/	exactly one entry on the shadow stack below. Functions may
/	repeat that process multiple times, in which case the body
/	of this gadget loops and unwinds as a natural consequence.
/
/	@param	rax,rdx,xmm0,xmm1,st0,st1 is return value
/	@see	test/libc/runtime/gc_test.c
/	<LIMBO>
__gc:	decq	__garbage(%rip)
	mov	__garbage(%rip),%r8
	mov	__garbage+16(%rip),%r9
	js	9f
	shl	$5,%r8
	lea	(%r9,%r8),%r8
	mov	8(%r8),%r9
	mov	16(%r8),%rdi
	push	24(%r8)
/	</LIMBO>
	push	%rbp
	mov	%rsp,%rbp
	sub	$0x40,%rsp
	push	%rax
	push	%rdx
	fstpl	-0x40(%rbp)
	fstpl	-0x30(%rbp)
	movaps	%xmm0,-0x20(%rbp)
	movaps	%xmm1,-0x10(%rbp)
	call	*%r9
	movaps	-0x10(%rbp),%xmm1
	movaps	-0x20(%rbp),%xmm0
	fldl	-0x30(%rbp)
	fldl	-0x40(%rbp)
	pop	%rdx
	pop	%rax
	leave
	ret
9:	call	abort
	.endfn	__gc,globl,hidden

	.bss
	.align	8
__garbage:
	.quad	0				# garbage.i
	.quad	0				# garbage.n
	.quad	0				# garbage.p
	.rept	INITIAL_CAPACITY
	.quad	0				# garbage.p[𝑖].frame
	.quad	0				# garbage.p[𝑖].fn
	.quad	0				# garbage.p[𝑖].arg
	.quad	0				# garbage.p[𝑖].ret
	.endr
	.endobj	__garbage,globl,hidden
	.previous

	.init.start 100,_init_garbage
	push	%rdi
	ezlea	__garbage+8,di
	pushpop	INITIAL_CAPACITY,%rax
	stosq
	lea	8(%rdi),%rax
	stosq
	pop	%rdi
	.init.end 100,_init_garbage
	.source	__FILE__
