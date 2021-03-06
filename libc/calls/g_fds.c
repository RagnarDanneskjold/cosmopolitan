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
#include "libc/bits/bits.h"
#include "libc/bits/pushpop.h"
#include "libc/calls/internal.h"
#include "libc/macros.h"
#include "libc/nt/runtime.h"
#include "libc/sysv/consts/fileno.h"

struct Fds g_fds;

INITIALIZER(300, _init_g_fds, {
  struct Fds *fds;
  fds = VEIL("D", &g_fds);
  pushmov(&fds->f, 3ul);
  pushmov(&fds->n, ARRAYLEN(fds->__init_p));
  fds->p = fds->__init_p;
  fds->__init_p[STDIN_FILENO].kind = pushpop(kFdFile);
  fds->__init_p[STDOUT_FILENO].kind = pushpop(kFdFile);
  fds->__init_p[STDERR_FILENO].kind = pushpop(kFdFile);
  fds->__init_p[STDIN_FILENO].handle = GetStdHandle(pushpop(kNtStdInputHandle));
  fds->__init_p[STDOUT_FILENO].handle =
      GetStdHandle(pushpop(kNtStdOutputHandle));
  fds->__init_p[STDERR_FILENO].handle =
      GetStdHandle(pushpop(kNtStdErrorHandle));
})
