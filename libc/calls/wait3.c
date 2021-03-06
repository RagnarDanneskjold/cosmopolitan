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
#include "libc/calls/calls.h"
#include "libc/calls/internal.h"
#include "libc/dce.h"
#include "libc/sysv/errfuns.h"

/**
 * Waits for status to change on any child process.
 *
 * @param opt_out_wstatus optionally returns status code, and *wstatus
 *     may be inspected using WEEXITSTATUS(), etc.
 * @param options can have WNOHANG, WUNTRACED, WCONTINUED, etc.
 * @param opt_out_rusage optionally returns accounting data
 * @return process id of terminated child or -1 w/ errno
 * @asyncsignalsafe
 */
int wait3(int *opt_out_wstatus, int options, struct rusage *opt_out_rusage) {
  if (!IsWindows()) {
    return wait4$sysv(-1, opt_out_wstatus, options, opt_out_rusage);
  } else {
    return enosys(); /* TODO(jart) */
  }
}
