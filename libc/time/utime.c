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
#include "libc/str/str.h"
#include "libc/calls/struct/timeval.h"
#include "libc/time/time.h"
#include "libc/time/utime.h"

/**
 * Changes last accessed/modified times on file.
 *
 * @param times if NULL means now
 * @return 0 on success or -1 w/ errno
 */
int utime(const char *path, const struct utimbuf *times) {
  struct timeval tv[2];
  memset(tv, 0, sizeof(tv));
  if (times) {
    tv[0].tv_sec = times->actime;
    tv[1].tv_sec = times->modtime;
  }
  return utimes(path, times ? tv : NULL);
}
