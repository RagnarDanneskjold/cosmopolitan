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

isgraph:.leafprologue
	.profilable
	xor	%eax,%eax
	cmp	$255,%edi
	ja	1f
	movslq	%edi,%rax
	ezlea	kCtype,cx
	mov	(%rcx,%rax),%al
	shr	$4,%al
	mov	%eax,%edx
	xor	%eax,%eax
	cmp	$32,%edi
	setne	%al
	and	%edx,%eax
1:	.leafepilogue
	.endfn	isgraph,globl
	.source	__FILE__
